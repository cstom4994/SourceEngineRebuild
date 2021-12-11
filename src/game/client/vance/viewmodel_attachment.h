//===================== AdV Software, 2019 =====================//
//
//	View-model attachment models
//
//==============================================================//

#ifndef VIEWMODEL_ATTACHMENT_H
#define VIEWMODEL_ATTACHMENT_H

class C_VanceViewModel;

class C_ViewmodelAttachmentModel : public C_BaseAnimating, public IHasOwner {
    DECLARE_CLASS(C_ViewmodelAttachmentModel, C_BaseAnimating);

public:
    virtual bool InitializeAsClientEntity(const char *pszModelName, RenderGroup_t renderGroup);

    virtual int GetSkin(void);

    void SetViewModel(C_VanceViewModel *pViewModel);

    virtual void FormatViewModelAttachment(int nAttachment, matrix3x4_t &attachmentToWorld);

    virtual void UncorrectViewModelAttachment(Vector &vOrigin);

    virtual bool IsViewModel() const { return true; }

    virtual RenderGroup_t GetRenderGroup(void);

    virtual ShadowType_t ShadowCastType() { return SHADOWS_NONE; }

    virtual C_BaseEntity *GetOwnerViaInterface(void);

private:
    CHandle<C_VanceViewModel> m_hViewmodel;
};

#endif // VIEWMODEL_ATTACHMENT_H