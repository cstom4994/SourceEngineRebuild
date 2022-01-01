//
// Created by Kaoruxun
//

#include "cbase.h"
#include "baseviewmodel_shared.h"

#if defined( CLIENT_DLL )
#define CHandViewModel C_HandViewModel
#endif

class CHandViewModel : public CBaseViewModel {
    DECLARE_CLASS( CHandViewModel, CBaseViewModel
    );

public:
    DECLARE_NETWORKCLASS();

private:
};

LINK_ENTITY_TO_CLASS( hand_viewmodel, CHandViewModel
);
IMPLEMENT_NETWORKCLASS_ALIASED(HandViewModel, DT_HandViewModel)

// For whatever reason the parent doesn't get sent
// And I don't really want to mess with BaseViewModel
// so now it does
BEGIN_NETWORK_TABLE(CHandViewModel, DT_HandViewModel)
#ifndef CLIENT_DLL

SendPropEHandle( SENDINFO_NAME(m_hMoveParent, moveparent)),
#else
RecvPropInt( RECVINFO_NAME( m_hNetworkMoveParent, moveparent ), 0, RecvProxy_IntToMoveParent ),
#endif
        END_NETWORK_TABLE()