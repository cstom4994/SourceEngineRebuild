//============================ AdV Software, 2019 ============================//
//
//	Base Vance Weapon
//
//============================================================================//

#include "cbase.h"
#include "viewmodel_attachment.h"
#include "vance_viewmodel.h"
#include "hl2_gamerules.h"
#include "view.h"
#include "functionproxy.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool C_ViewmodelAttachmentModel::InitializeAsClientEntity(const char *pszModelName, RenderGroup_t renderGroup) {
    if (BaseClass::InitializeAsClientEntity(pszModelName, renderGroup)) {
        // EF_NODRAW so it won't get drawn directly. We want to draw it from the viewmodel.
        AddEffects(EF_BONEMERGE | EF_BONEMERGE_FASTCULL | EF_NODRAW);
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void C_ViewmodelAttachmentModel::SetViewModel(C_VanceViewModel *pViewModel) {
    m_hViewmodel.Set(pViewModel);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
int C_ViewmodelAttachmentModel::GetSkin(void) {
    if (m_hViewmodel->GetViewModelType() == VMTYPE_L4D) {
        return m_hViewmodel->GetSkin();
    }

    return 0;
}

void FormatViewModelAttachment(Vector &vOrigin, bool bInverse);

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void C_ViewmodelAttachmentModel::FormatViewModelAttachment(int nAttachment, matrix3x4_t &attachmentToWorld) {
    Vector vecOrigin;
    MatrixPosition(attachmentToWorld, vecOrigin);
    ::FormatViewModelAttachment(vecOrigin, false);
    PositionMatrix(vecOrigin, attachmentToWorld);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void C_ViewmodelAttachmentModel::UncorrectViewModelAttachment(Vector &vOrigin) {
    // Unformat the attachment.
    ::FormatViewModelAttachment(vOrigin, true);
}

RenderGroup_t C_ViewmodelAttachmentModel::GetRenderGroup(void) {
    return m_hViewmodel->GetRenderGroup();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_BaseEntity *C_ViewmodelAttachmentModel::GetOwnerViaInterface(void) {
    return m_hViewmodel->GetOwnerViaInterface();
}