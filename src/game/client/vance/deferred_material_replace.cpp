//====== Copyright � Sandern Corporation, All rights reserved. ===========//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "filesystem.h"
#include "utlbuffer.h"
#include "igamesystem.h"
#include "deferred_material_passthru.h"
#include "deferred_rt.h"
#include "materialsystem/imaterialvar.h"
#include "materialsystem/itexture.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


static int matCount = 0;

CON_COMMAND(print_num_replaced_mats, "") {
    ConColorMsg(COLOR_GREEN, "%d replaced materials\n", matCount);
}

bool replMatPossible = true;

//-----------------------------------------------------------------------------
// List of materials that should be replaced
//-----------------------------------------------------------------------------
static const char *const pszShaderReplaceDict[][2] = {
        "VertexLitGeneric", "SDK_VertexLitGeneric",
        "LightmappedGeneric", "SDK_LightmappedGeneric",
        "WorldVertexTransition", "SDK_WorldVertexTransition",
        //"LightmappedGeneric_Decal",		"SDK_LightmappedGeneric_Decal",
};
static const int iNumShaderReplaceDict = ARRAYSIZE(pszShaderReplaceDict);

#include "icommandline.h"

// Copied from cdeferred_manager_client.cpp
static void ShaderReplaceReplMat(const char *szNewShadername, IMaterial *pMat) {
    const char *pszOldShadername = pMat->GetShaderName();
    const char *pszMatname = pMat->GetName();

    KeyValues *msg = new KeyValues(szNewShadername);

    int nParams = pMat->ShaderParamCount();
    IMaterialVar **pParams = pMat->GetShaderParams();

    char str[512];

    for (int i = 0; i < nParams; ++i) {
        IMaterialVar *pVar = pParams[i];
        const char *pVarName = pVar->GetName();

        if (!V_stricmp("$flags", pVarName) ||
            !V_stricmp("$flags_defined", pVarName) ||
            !V_stricmp("$flags2", pVarName) ||
            !V_stricmp("$flags_defined2", pVarName))
            continue;

        switch (pVar->GetType()) {
            case MATERIAL_VAR_TYPE_FLOAT:
                msg->SetFloat(pVarName, pVar->GetFloatValue());
                break;

            case MATERIAL_VAR_TYPE_INT:
                msg->SetInt(pVarName, pVar->GetIntValue());
                break;

            case MATERIAL_VAR_TYPE_STRING:
                msg->SetString(pVarName, pVar->GetStringValue());
                break;

            case MATERIAL_VAR_TYPE_FOURCC:
                //Assert( 0 ); // JDTODO
                break;

            case MATERIAL_VAR_TYPE_VECTOR: {
                const float *pVal = pVar->GetVecValue();
                int dim = pVar->VectorSize();
                switch (dim) {
                    case 1:
                        V_sprintf_safe(str, "[%f]", pVal[0]);
                        break;
                    case 2:
                        V_sprintf_safe(str, "[%f %f]", pVal[0], pVal[1]);
                        break;
                    case 3:
                        V_sprintf_safe(str, "[%f %f %f]", pVal[0], pVal[1], pVal[2]);
                        break;
                    case 4:
                        V_sprintf_safe(str, "[%f %f %f %f]", pVal[0], pVal[1], pVal[2], pVal[3]);
                        break;
                    default:
                        Assert(0);
                        *str = 0;
                }
                msg->SetString(pVarName, str);
            }
                break;

            case MATERIAL_VAR_TYPE_MATRIX: {
                const float *pVal = pVar->GetMatrixValue().Base();
                V_sprintf_safe(str,
                               "[%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f]",
                               pVal[0], pVal[1], pVal[2], pVal[3],
                               pVal[4], pVal[5], pVal[6], pVal[7],
                               pVal[8], pVal[9], pVal[10], pVal[11],
                               pVal[12], pVal[13], pVal[14], pVal[15]);
                msg->SetString(pVarName, str);
            }
                break;

            case MATERIAL_VAR_TYPE_TEXTURE:
                msg->SetString(pVarName, pVar->GetTextureValue()->GetName());
                break;

            case MATERIAL_VAR_TYPE_MATERIAL:
                msg->SetString(pVarName, pVar->GetMaterialValue()->GetName());
                break;
        }
    }

    bool alphaBlending = pMat->IsTranslucent() || pMat->GetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT);
    bool translucentOverride = pMat->IsAlphaTested() || pMat->GetMaterialVarFlag(MATERIAL_VAR_ALPHATEST);

    bool bDecal = pszOldShadername != NULL && Q_stristr(pszOldShadername, "decal") != NULL ||
                  pszMatname != NULL && Q_stristr(pszMatname, "decal") != NULL ||
                  pMat->GetMaterialVarFlag(MATERIAL_VAR_DECAL);

    if (bDecal)
        msg->SetInt("$decal", 1);

    if (alphaBlending)
        msg->SetInt("$translucent", 1);

    if (translucentOverride)
        msg->SetInt("$alphatest", 1);

    if (pMat->IsTwoSided() || pMat->GetMaterialVarFlag(MATERIAL_VAR_NOCULL))
        msg->SetInt("$nocull", 1);

    if (pMat->GetMaterialVarFlag(MATERIAL_VAR_ADDITIVE))
        msg->SetInt("$additive", 1);

    if (pMat->GetMaterialVarFlag(MATERIAL_VAR_MODEL))
        msg->SetInt("$model", 1);

    if (pMat->GetMaterialVarFlag(MATERIAL_VAR_NOFOG))
        msg->SetInt("$nofog", 1);

    if (pMat->GetMaterialVarFlag(MATERIAL_VAR_IGNOREZ))
        msg->SetInt("$ignorez", 1);

    if (pMat->GetMaterialVarFlag(MATERIAL_VAR_HALFLAMBERT))
        msg->SetInt("$halflambert", 1);

    pMat->SetShaderAndParams(msg);

    pMat->RefreshPreservingMaterialVars();

    msg->deleteThis();
}

const char *Console_GetLastLine(size_t errorSize) {
    fseek(stdout, 0, SEEK_END);
    for (int pos = ftell(stdout); pos != -1; pos--) {
        char currentCharacter;
        fread(&currentCharacter, 1, 1, stdout);

        if (currentCharacter == '\0') {
            fseek(stdout, pos, SEEK_SET);
            break;
        }
    }

    char *pszLine = new char[errorSize];
    fread(pszLine, 1, errorSize, stdout);

    char *pszRet = NULL;
    strcpy(pszRet, pszLine);
    delete pszLine;

    return pszRet;
}

#ifdef _DEBUG
#define DebuggerBreakOnError(pszError) if (V_stricmp(Console_GetLastLine(strlen(pszError)), pszError) == 0) \
    DebuggerBreak();
#else
#define DebuggerBreakOnError(pszError)
#endif

IMaterial *CDeferredMaterialSystem::FindProceduralMaterial(const char *pMaterialName, const char *pTextureGroupName,
                                                           KeyValues *pVMTKeyValues) {
    const char *pShaderName = pVMTKeyValues->GetName();
    for (const char *const *row: pszShaderReplaceDict) {
        if (V_stristr(pShaderName, row[0])) {
            pVMTKeyValues->SetName(row[1]);
            matCount++;
            break;
        }
    }

    IMaterial *pMaterial = BaseClass::FindProceduralMaterial(pMaterialName, pTextureGroupName, pVMTKeyValues);
    //	DebuggerBreakOnError("ShaderAPIDX8::CreateD3DTexture: D3DERR_INVALIDCALL\n");
    if (!pMaterial)
        DebuggerBreak();
    return pMaterial;
}

IMaterial *CDeferredMaterialSystem::CreateMaterial(const char *pMaterialName, KeyValues *pVMTKeyValues) {
    const char *pShaderName = pVMTKeyValues->GetName();
    for (const char *const *row: pszShaderReplaceDict) {
        if (V_stristr(pShaderName, row[0])) {
            pVMTKeyValues->SetName(row[1]);
            matCount++;
            break;
        }
    }

    IMaterial *pMaterial = BaseClass::CreateMaterial(pMaterialName, pVMTKeyValues);
    //	DebuggerBreakOnError("ShaderAPIDX8::CreateD3DTexture: D3DERR_INVALIDCALL\n");
    if (!pMaterial)
        DebuggerBreak();
    return pMaterial;
}

IMaterial *CDeferredMaterialSystem::ReplaceMaterialInternal(IMaterial *pMat) const {
    if (!pMat || pMat->IsErrorMaterial() || pMat->InMaterialPage())
        return pMat;

    const char *pShaderName = pMat->GetShaderName();
    if (pShaderName) {
        for (const char *const *row: pszShaderReplaceDict) {
            if (V_stristr(pShaderName, row[0])) {
                ShaderReplaceReplMat(row[1], pMat);
                matCount++;
                break;
            }
        }
    }
    return pMat;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class ReplacementSystem : public CAutoGameSystem {
public:
    ReplacementSystem() : m_pOldMaterialSystem(NULL) {}

    virtual bool Init() {
        Enable();
        return true;
    }

    virtual void Shutdown() {
        Disable();
    }

    virtual void LevelShutdownPostEntity() { /*matCount = 0;*/ }

    void Enable();

    void Disable();

    bool IsEnabled() const { return m_pOldMaterialSystem != NULL; }

private:
    CDeferredMaterialSystem m_MatSysPassTru;
    IMaterialSystem *m_pOldMaterialSystem;
};

static ReplacementSystem s_ReplacementSystem;

void ReplacementSystem::Enable() {

    if (m_pOldMaterialSystem || !replMatPossible)
        return;

    DevMsg("Enabled material replacement system\n");

    // Replace material system
    m_MatSysPassTru.InitPassThru(materials);

    m_pOldMaterialSystem = materials;
    materials = &m_MatSysPassTru;
    g_pMaterialSystem = &m_MatSysPassTru;
    engine->Mat_Stub(&m_MatSysPassTru);

}

void ReplacementSystem::Disable() {
    if (m_pOldMaterialSystem) {
        DevMsg("Disabled material replacement system\n");

        materials = m_pOldMaterialSystem;
        g_pMaterialSystem = m_pOldMaterialSystem;
        engine->Mat_Stub(m_pOldMaterialSystem);
        m_pOldMaterialSystem = NULL;
    }

}

CON_COMMAND_F(toggle_replmat, "Toggles the material replacement system", FCVAR_CHEAT) {
    if (s_ReplacementSystem.IsEnabled()) {
        s_ReplacementSystem.Disable();
    } else {
        s_ReplacementSystem.Enable();
    }

    materials->UncacheAllMaterials();
    materials->CacheUsedMaterials();
    materials->ReloadMaterials();
}
