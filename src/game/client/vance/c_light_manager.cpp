#include "cbase.h"
#include "IDeferredExt.h"
#include "viewrender.h"
#include "view_scene.h"
#include "c_env_global_light.h"
#include "mathlib/vmatrix.h"
#include "materialsystem/imaterialvar.h"
#include "c_light_manager.h"
#include "engine/ivdebugoverlay.h"

CON_COMMAND(deferred_lights_count, "Get amount of deferred light sources") {
    Msg("amount of deferred lights: %i\n", GetLightingManager()->CountLight());
}

static void Volumetrics_change_Callback(IConVar *var, const char *pOldValue, float flOldValue) {
    if (GetLightingManager()->GetViewVolumetrics() != NULL) {
        GetLightingManager()->ClearVolumetricsMesh();
    }
}

ConVar r_volumetrics_subdiv("r_volumetrics_subdiv", "128", 0, "", Volumetrics_change_Callback);
ConVar r_volumetrics_distance("r_volumetrics_distance", "1024", 0, "", Volumetrics_change_Callback);

static CLightingManager __g_lightingMan;

CLightingManager *GetLightingManager() {
    return &__g_lightingMan;
}

static void MatrixSourceToDeviceSpace(VMatrix &m) {
    Vector x, y, z;
    m.GetBasisVectors(x, y, z);
    m.SetBasisVectors(-y, z, -x);
}

float DistanceAtWhichBrightnessIsLessThan(LightDesc_t const &light, float flAmount) {
    float bright = light.m_Color.Length();
    if (bright > 0.0) {
        flAmount /= light.m_Color.Length();

        // calculate terms for quadratic equation
        float a = flAmount * light.m_Attenuation2;
        float b = flAmount * light.m_Attenuation1;
        float c = flAmount * light.m_Attenuation0 - 1;

        float r0, r1;
        if (SolveQuadratic(a, b, c, r0, r1)) {
            float rslt = MAX(0, MAX(r0, r1));
#ifdef _DEBUG
            if (rslt > 0.0)
            {
                float fltest = 1.0 / (light.m_Attenuation0 + rslt * light.m_Attenuation1 + rslt * rslt * light.m_Attenuation2);
                Assert(fabs(fltest - flAmount) < 0.1);
            }
#endif
            return rslt;
        }
    }
    return 0;
}

#define APPLYSIGN(posneg, incr) ( ( posneg ) ? ( incr ) : ( - ( incr ) ) )

static int s_CubeIndices[] = {
        5, 4, 6,                                                // front
        6, 7, 5,
        4, 0, 2,                                                // rside
        2, 6, 4,
        2, 0, 1,                                                // back
        1, 3, 2,
        1, 0, 4,                                                // top
        4, 5, 1,
        6, 2, 3,                                                // bot
        3, 7, 6,
        5, 7, 3,                                                // lside
        3, 1, 5
};

static int s_PyramidIndices[] = {
        1, 0, 4, // top

        2, 3, 4, // bottom

        3, 1, 4, // right

        0, 2, 4, // right

        0, 1, 3, // end cap
        3, 2, 0
};

static int DrawWorldSpaceLightCube(
        CMatRenderContextPtr &pRenderContext,
        LightDesc_t const &light,
        IMaterial *mat,
        int nIndex) {
    CMeshBuilder meshBuilder;
    IMesh *pMesh = pRenderContext->GetDynamicMesh(true);
    meshBuilder.Begin(pMesh, MATERIAL_TRIANGLES, 8, 6 * 3 * 2);

    Vector color_intens = light.m_Color;
    Vector spot_dir = light.m_Direction;
    float rad = DistanceAtWhichBrightnessIsLessThan(light, 0.01f);

    Vector vecProjectionPlane0 = CrossProduct(spot_dir, Vector(0, 1, 0)) + CrossProduct(spot_dir, Vector(1, 0, 0));
    vecProjectionPlane0.NormalizeInPlace();
    Vector vecProjectionPlane1 = CrossProduct(spot_dir, vecProjectionPlane0);
    Assert(fabs(DotProduct(spot_dir, vecProjectionPlane0)) < 0.01);
    Assert(fabs(DotProduct(spot_dir, vecProjectionPlane1)) < 0.01);
    Assert(fabs(DotProduct(vecProjectionPlane0, vecProjectionPlane1)) < 0.01);

    for (int corner = 0; corner < 8; corner++) {
        Vector vecPnt = light.m_Position;
        vecPnt.x += APPLYSIGN(corner & 1, rad);
        vecPnt.y += APPLYSIGN(corner & 2, rad);
        vecPnt.z += APPLYSIGN(corner & 4, rad);

        meshBuilder.Position3fv(vecPnt.Base());
        meshBuilder.AdvanceVertex();
    }
    // now, output indices
    for (int i = ARRAYSIZE(s_CubeIndices) - 1; i >= 0; i--) {
        meshBuilder.FastIndex(s_CubeIndices[i] + nIndex);
    }

    meshBuilder.End();

    pRenderContext->Bind(mat);
    pRenderContext->SetLight(0, light);
    pMesh->Draw();

    return 8;
}

int DrawWorldSpaceLightPyramid(
        CMatRenderContextPtr &pRenderContext,
        LightDesc_t const &light,
        IMaterial *mat,
        int nIndex) {
    CMeshBuilder meshBuilder;
    IMesh *pMesh = pRenderContext->GetDynamicMesh(true);
    meshBuilder.Begin(pMesh, MATERIAL_TRIANGLES, 5, 6 + 4 * 3);

    Vector color_intens = light.m_Color;
    Vector spot_dir = light.m_Direction;
    // now, we need to find two vectors perpendicular to each other and the ray direction
    Vector vecProjectionPlane0 = CrossProduct(spot_dir, Vector(0, 1, 0)) + CrossProduct(spot_dir, Vector(1, 0, 0));
    vecProjectionPlane0.NormalizeInPlace();
    Vector vecProjectionPlane1 = CrossProduct(spot_dir, vecProjectionPlane0);
    Assert(fabs(DotProduct(spot_dir, vecProjectionPlane0)) < 0.01);
    Assert(fabs(DotProduct(spot_dir, vecProjectionPlane1)) < 0.01);
    Assert(fabs(DotProduct(vecProjectionPlane0, vecProjectionPlane1)) < 0.01);

    float dist = DistanceAtWhichBrightnessIsLessThan(light, 0.01f);

    float flSpreadPerDistance = sqrt(1.0 / (light.m_PhiDot * light.m_PhiDot) - 1);

    float flEndRad = 2.0 * dist * flSpreadPerDistance;

    for (int corner = 0; corner < 5; corner++) {
        Vector vecPnt = light.m_Position;
        switch (corner) {
            case 0:
                vecPnt += dist * spot_dir - flEndRad * vecProjectionPlane0 + flEndRad * vecProjectionPlane1;
                break;

            case 1:
                vecPnt += dist * spot_dir + flEndRad * vecProjectionPlane0 + flEndRad * vecProjectionPlane1;
                break;

            case 2:
                vecPnt += dist * spot_dir - flEndRad * vecProjectionPlane0 - flEndRad * vecProjectionPlane1;
                break;

            case 3:
                vecPnt += dist * spot_dir + flEndRad * vecProjectionPlane0 - flEndRad * vecProjectionPlane1;
                break;
        }

        meshBuilder.Position3fv(vecPnt.Base());
        meshBuilder.AdvanceVertex();
    }

    // now, output indices
    for (int i = ARRAYSIZE(s_PyramidIndices) - 1; i >= 0; i--) {
        meshBuilder.FastIndex(s_PyramidIndices[i] + nIndex);
    }

    meshBuilder.End();

    pRenderContext->Bind(mat);
    pRenderContext->SetLight(0, light);
    pMesh->Draw();

    return 5;

}

void CLightingManager::AddLight(volume_light_t *l) {
    Assert(!m_hVolumetricLights.HasElement(l));

    m_hVolumetricLights.AddToTail(l);
}

bool CLightingManager::RemoveLight(volume_light_t *l) {
    return m_hVolumetricLights.FindAndRemove(l);
}

void CLightingManager::AddLight(LightDesc_t *l) {
    Assert(!m_hLights.HasElement(l));

    m_hLights.AddToTail(l);
}

bool CLightingManager::RemoveLight(LightDesc_t *l) {
    return m_hLights.FindAndRemove(l);
}

void CLightingManager::CommitLights() {
}

void CLightingManager::FlushLights() {
    m_hVolumetricLights.RemoveAll();
    m_hLights.RemoveAll();
}

void CLightingManager::PrepareShadowLights() {
    /*FOR_EACH_VEC_FAST(def_light_t*, m_hDeferredLights, l)
    {
        if (l->bSpotShadow)
            l->UpdateMatrix();
    }
    FOR_EACH_VEC_FAST_END*/
    return;
}

void CLightingManager::RenderLights(const CViewSetup &view) {
/*	CMatRenderContextPtr pRenderContext(materials);

	FOR_EACH_VEC_FAST(LightDesc_t*, m_hLights, l)
	{
		if (l->m_Type == MATERIAL_LIGHT_POINT)
			DrawWorldSpaceLightCube(pRenderContext, *l, m_matLightMaterial, 0);
		else if (l->m_Type == MATERIAL_LIGHT_SPOT)
			DrawWorldSpaceLightPyramid(pRenderContext, *l, m_matLightMaterial, 0);
	}
	FOR_EACH_VEC_FAST_END;
	*/
}

void CLightingManager::LevelInitPreEntity() {
    if (!m_matVolumetricsMaterial.IsValid()) {
        m_matVolumetricsMaterial.Init(materials->FindMaterial("shaders/light_volumetrics", TEXTURE_GROUP_OTHER));
        if (m_matVolumetricsMaterial->IsErrorMaterial())
            Warning("Couldn't find volumetric light material: %s\n", "shaders/light_volumetrics");
    }
    if (!m_matLightMaterial.IsValid()) {
        m_matLightMaterial.Init(materials->FindMaterial("shaders/deferred_lights", TEXTURE_GROUP_OTHER));
        if (m_matLightMaterial->IsErrorMaterial())
            Warning("Couldn't find volumetric light material: %s\n", "shaders/deferred_lights");
    }

    FlushLights();
}

void CLightingManager::RenderVolumetrics(const CViewSetup &view) {
    CMatRenderContextPtr pRenderContext(materials);
    pRenderContext->SetFlashlightMode(true);

    FOR_EACH_VEC_FAST(volume_light_t*, m_hVolumetricLights, l)
            {
                if (m_meshViewVolumetrics == NULL) {
                    RebuildVolumetricMesh();
                }

                // skip rendering this volumetric light if handle is invalid
                // it means that light is not even in our view or we cant see it anyway
                if (*l->handle == CLIENTSHADOW_INVALID_HANDLE)
                    continue;

                UpdateScreenEffectTexture(0, view.x, view.y, view.width, view.height);

                FlashlightState_t state = *l->state;
                state.m_Color[0] *= l->intensity;
                state.m_Color[1] *= l->intensity;
                state.m_Color[2] *= l->intensity;
                state.m_Color[3] *= l->intensity;

                pRenderContext->SetFlashlightStateEx(state, l->spotWorldToTex, l->depth);

                //var = m_matVolumetricsMaterial->FindVar("$iscsm", NULL);
                //var->SetIntValue(1);
                ShadowHandle_t shadowHandle = g_pClientShadowMgr->GetShadowHandle(*l->handle);
                const Frustum_t &frustum = shadowmgr->GetFlashlightFrustum(shadowHandle);

                for (int i = 0; i < 6; i++) {
                    Vector4D plane;
                    VectorMultiply(frustum.GetPlane(i)->normal, 1, plane.AsVector3D());
                    plane.w = frustum.GetPlane(i)->dist + 0.1f;
                    pRenderContext->PushCustomClipPlane(plane.Base());
                }


                matrix3x4_t viewTransform;
                AngleMatrix(view.angles, view.origin, viewTransform);

                pRenderContext->MatrixMode(MATERIAL_MODEL);
                pRenderContext->PushMatrix();
                pRenderContext->LoadMatrix(viewTransform);

                pRenderContext->Bind(m_matVolumetricsMaterial);
                m_meshViewVolumetrics->Draw();

                pRenderContext->MatrixMode(MATERIAL_MODEL);
                pRenderContext->PopMatrix();

                for (int i = 0; i < 6; i++) {
                    pRenderContext->PopCustomClipPlane();
                }

            }
    FOR_EACH_VEC_FAST_END;

    pRenderContext->SetFlashlightMode(false);
    return;
}


void CLightingManager::ClearVolumetricsMesh() {
    if (m_meshViewVolumetrics != NULL) {
        CMatRenderContextPtr pRenderContext(materials);
        pRenderContext->DestroyStaticMesh(m_meshViewVolumetrics);
        m_meshViewVolumetrics = NULL;
    }
}

void CLightingManager::RebuildVolumetricMesh() {
    ClearVolumetricsMesh();

    CViewSetup setup;
    setup = m_view;
    setup.origin = vec3_origin;
    setup.angles = vec3_angle;
    setup.zFar = r_volumetrics_distance.GetFloat();

    VMatrix world2View, view2Proj, world2Proj, world2Pixels;
    render->GetMatricesForView(setup, &world2View, &view2Proj, &world2Proj, &world2Pixels);
    VMatrix proj2world;
    MatrixInverseGeneral(world2Proj, proj2world);

    const Vector origin(vec3_origin);
    QAngle angles(vec3_angle);
    Vector fwd, right, up;
    AngleVectors(angles, &fwd, &right, &up);

    Vector nearPlane[4];
    Vector farPlane[4];
    Vector3DMultiplyPositionProjective(proj2world, Vector(-1, -1, 1), farPlane[0]);
    Vector3DMultiplyPositionProjective(proj2world, Vector(1, -1, 1), farPlane[1]);
    Vector3DMultiplyPositionProjective(proj2world, Vector(1, 1, 1), farPlane[2]);
    Vector3DMultiplyPositionProjective(proj2world, Vector(-1, 1, 1), farPlane[3]);

    Vector3DMultiplyPositionProjective(proj2world, Vector(-1, -1, 0), nearPlane[0]);
    Vector3DMultiplyPositionProjective(proj2world, Vector(1, -1, 0), nearPlane[1]);
    Vector3DMultiplyPositionProjective(proj2world, Vector(1, 1, 0), nearPlane[2]);
    Vector3DMultiplyPositionProjective(proj2world, Vector(-1, 1, 0), nearPlane[3]);

    const Vector vecDirections[3] = {
            (farPlane[0] - vec3_origin),
            (farPlane[1] - farPlane[0]),
            (farPlane[3] - farPlane[0]),
    };

    const VertexFormat_t vertexFormat = VERTEX_POSITION | VERTEX_TEXCOORD_SIZE(0, 2);
    CMatRenderContextPtr pRenderContext(materials);
    m_meshViewVolumetrics = pRenderContext->CreateStaticMesh(vertexFormat, TEXTURE_GROUP_OTHER);

    const int iCvarSubDiv = r_volumetrics_subdiv.GetInt();
    int iCurrentVolumetricsSubDiv = (iCvarSubDiv > 2) ? iCvarSubDiv : 3;

    CMeshBuilder meshBuilder;
    meshBuilder.Begin(m_meshViewVolumetrics, MATERIAL_TRIANGLES, iCurrentVolumetricsSubDiv * 6 - 4);

    for (int x = 1; x < iCurrentVolumetricsSubDiv * 2; x++) {
        // never 0.0 or 1.0
        float flFracX = float(x) / (iCurrentVolumetricsSubDiv * 2);
        flFracX = powf(flFracX, 3.0f);
        //flFracX = powf(flFracX, m_flVolumetricsQualityBias);

        Vector v00 = origin + vecDirections[0] * flFracX;
        Vector v10 = v00 + vecDirections[1] * flFracX;
        Vector v11 = v10 + vecDirections[2] * flFracX;
        Vector v01 = v00 + vecDirections[2] * flFracX;

        meshBuilder.Position3f(XYZ(v00));
        meshBuilder.TexCoord2f(0, 0.0f, 0.0f);
        meshBuilder.AdvanceVertex();

        meshBuilder.Position3f(XYZ(v10));
        meshBuilder.TexCoord2f(0, 0.0f, 0.0f);
        meshBuilder.AdvanceVertex();

        meshBuilder.Position3f(XYZ(v11));
        meshBuilder.TexCoord2f(0, 0.0f, 0.0f);
        meshBuilder.AdvanceVertex();

        meshBuilder.Position3f(XYZ(v00));
        meshBuilder.TexCoord2f(0, 0.0f, 0.0f);
        meshBuilder.AdvanceVertex();

        meshBuilder.Position3f(XYZ(v11));
        meshBuilder.TexCoord2f(0, 0.0f, 0.0f);
        meshBuilder.AdvanceVertex();

        meshBuilder.Position3f(XYZ(v01));
        meshBuilder.TexCoord2f(0, 0.0f, 0.0f);
        meshBuilder.AdvanceVertex();
    }

    meshBuilder.End();
}

void CLightingManager::SetRenderConstants(const VMatrix &ScreenToWorld,
                                          const CViewSetup &setup) {
    m_matScreenToWorld = ScreenToWorld;

    m_vecViewOrigin = setup.origin;
    AngleVectors(setup.angles, &m_vecForward);

    m_flzNear = setup.zNear;
    m_view = setup;
}