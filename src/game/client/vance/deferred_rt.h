#ifndef DEFERRED_RT_H
#define DEFERRED_RT_H

class ITexture;

float GetDepthMapDepthResolution(float zDelta);

void GetGBufferResolution(int &iW, int &iH);

void DefRTsOnModeChanged();

void InitDeferredRTs(bool bInitial = false);

ITexture *GetDefRT_MR();

ITexture *GetDefRT_PosNormal(bool position = true);

ITexture *GetDefRT_Albedo();

ITexture *GetDefRT_Light();

#endif
