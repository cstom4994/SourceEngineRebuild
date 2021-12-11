#ifndef DEFERRED_COMMON_H
#define DEFERRED_COMMON_H

#define PROFILER_DECLARE CFastTimer __pft; __pft.Start()
#define PROFILER_RESTART __pft.Start();
#define PROFILER_OUTPUT(line, format) __pft.End();\
    engine->Con_NPrintf( line, format, __pft.GetDuration().GetCycles() )

#define PATHLOCATION_PROJECTABLE_SCRIPTS "scripts/vguiprojected"

#include "IDeferredExt.h"
#include "deferred_rt.h"

#include "util_shared.h"
#include "mathlib/ssemath.h"
#include "flashlighteffect.h"
#include "deferred_material_passthru.h"

#define QUEUE_FIRE(functionName, ...){\
        CMatRenderContextPtr pRenderContext( materials );\
        ICallQueue *pCallQueue = pRenderContext->GetCallQueue();\
        if ( pCallQueue )\
            pCallQueue->QueueCall( GetDeferredExt(), &IDeferredExtension::functionName, __VA_ARGS__ );\
        else\
            GetDeferredExt()->functionName( __VA_ARGS__ );\
    }

#define SATURATE(x) ( Clamp( (x), 0.f, 1.f ) )

inline void DrawLightPassFullscreen(IMaterial *pMaterial, int w, int t) {
    CMatRenderContextPtr pRenderContext(materials);
    pRenderContext->DrawScreenSpaceRectangle(pMaterial,
                                             0, 0, w, t,
                                             0, 0, w - 1.0f, t - 1.0f,
                                             w, t
    );
}

FORCEINLINE void CalcBoundaries(Vector *list, const int &num, Vector &min, Vector &max) {
    Assert(num > 0);
    min = *list;
    max = *list;

    for (int i = 1; i < num; i++) {
        for (int x = 0; x < 3; x++) {
            min[x] = Min(min[x], list[i][x]);
            max[x] = Max(max[x], list[i][x]);
        }
    }
}

FORCEINLINE void DebugDrawCross(const Vector &pos, float size, float lifetime) {
    DebugDrawLine(pos - Vector(0, 0, size), pos + Vector(0, 0, size), 0, 255, 0, true, lifetime);
    DebugDrawLine(pos - Vector(0, size, 0), pos + Vector(0, size, 0), 255, 0, 0, true, lifetime);
    DebugDrawLine(pos - Vector(size, 0, 0), pos + Vector(size, 0, 0), 0, 0, 255, true, lifetime);
}

FORCEINLINE void DrawFrustum(VMatrix &invScreenToWorld) {
    const Vector normalized_points[8] = {
            Vector(-1, 1, 0),
            Vector(1, 1, 0),
            Vector(1, -1, 0),
            Vector(-1, -1, 0),

            Vector(-1, 1, 1),
            Vector(1, 1, 1),
            Vector(1, -1, 1),
            Vector(-1, -1, 1)
    };
    Vector _points[8];

    for (int i = 0; i < 8; i++)
        Vector3DMultiplyPositionProjective(invScreenToWorld, normalized_points[i], _points[i]);

    for (int i = 0; i < 8; i++)
        DebugDrawCross(_points[i], 10.0f, -1.0f);

    DebugDrawLine(_points[0], _points[1], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[1], _points[2], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[2], _points[3], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[0], _points[3], 255, 255, 255, true, -1.0f);

    DebugDrawLine(_points[4], _points[5], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[6], _points[5], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[6], _points[7], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[4], _points[7], 255, 255, 255, true, -1.0f);

    DebugDrawLine(_points[0], _points[4], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[1], _points[5], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[2], _points[6], 255, 255, 255, true, -1.0f);
    DebugDrawLine(_points[3], _points[7], 255, 255, 255, true, -1.0f);
}

// returns false when no intersection
FORCEINLINE bool IntersectFrustumWithFrustum(const VMatrix &invScreenToWorld_a, const VMatrix &invScreenToWorld_b) {
    static const fltx4 ALIGN128 _normPos[8] ALIGN128_POST = {
            {-1.f, 1.f,  0.f, 1.f},
            {1.f,  1.f,  0.f, 1.f},
            {1.f,  -1.f, 0.f, 1.f},
            {-1.f, -1.f, 0.f, 1.f},
            {-1.f, 1.f,  1.f, 1.f},
            {1.f,  1.f,  1.f, 1.f},
            {1.f,  -1.f, 1.f, 1.f},
            {-1.f, -1.f, 1.f, 1.f}
    };

    fltx4 _pointx4[2][8];
    fltx4 axes[22];
    fltx4 on_frustum_directions[2][6];

    fltx4 _invScreenToWorldAInSSE[4], _invScreenToWorldBInSSE[4];

    _invScreenToWorldAInSSE[0] = LoadUnalignedSIMD(invScreenToWorld_a[0]);
    _invScreenToWorldAInSSE[1] = LoadUnalignedSIMD(invScreenToWorld_a[1]);
    _invScreenToWorldAInSSE[2] = LoadUnalignedSIMD(invScreenToWorld_a[2]);
    _invScreenToWorldAInSSE[3] = LoadUnalignedSIMD(invScreenToWorld_a[3]);

    TransposeSIMD
            (
                    _invScreenToWorldAInSSE[0],
                    _invScreenToWorldAInSSE[1],
                    _invScreenToWorldAInSSE[2],
                    _invScreenToWorldAInSSE[3]
            );

    _invScreenToWorldBInSSE[0] = LoadUnalignedSIMD(invScreenToWorld_b[0]);
    _invScreenToWorldBInSSE[1] = LoadUnalignedSIMD(invScreenToWorld_b[1]);
    _invScreenToWorldBInSSE[2] = LoadUnalignedSIMD(invScreenToWorld_b[2]);
    _invScreenToWorldBInSSE[3] = LoadUnalignedSIMD(invScreenToWorld_b[3]);

    TransposeSIMD
            (
                    _invScreenToWorldBInSSE[0],
                    _invScreenToWorldBInSSE[1],
                    _invScreenToWorldBInSSE[2],
                    _invScreenToWorldBInSSE[3]
            );

    for (int i = 0; i < 8; i++) {
        _pointx4[0][i] = FourDotProducts(_invScreenToWorldAInSSE, _normPos[i]);

        float _w = SubFloat(_pointx4[0][i], 3);
        if (_w != 0) {
            _w = 1.0f / _w;
        }

        _pointx4[0][i] = MulSIMD(_pointx4[0][i], ReplicateX4(_w));

        _pointx4[1][i] = FourDotProducts(_invScreenToWorldBInSSE, _normPos[i]);

        _w = SubFloat(_pointx4[1][i], 3);
        if (_w != 0) {
            _w = 1.0f / _w;
        }

        _pointx4[1][i] = MulSIMD(_pointx4[1][i], ReplicateX4(_w));
    }

    for (int i = 0; i < 2; i++) // build minimal frustum frame
    {
        on_frustum_directions[i][0] = SubSIMD(_pointx4[i][1], _pointx4[i][0]); // viewplane x
        on_frustum_directions[i][1] = SubSIMD(_pointx4[i][3], _pointx4[i][0]); // viewplane y

        on_frustum_directions[i][2] = SubSIMD(_pointx4[i][0], _pointx4[i][4]); // frustum 0 0
        on_frustum_directions[i][3] = SubSIMD(_pointx4[i][1], _pointx4[i][5]); // frustum 1 0
        on_frustum_directions[i][4] = SubSIMD(_pointx4[i][2], _pointx4[i][6]); // frustum 1 1
        on_frustum_directions[i][5] = SubSIMD(_pointx4[i][3], _pointx4[i][7]); // frustum 0 1
    }

    for (int x = 0; x < 2; x++) {
        NormalizeInPlaceSIMD(on_frustum_directions[x][0]);
        NormalizeInPlaceSIMD(on_frustum_directions[x][1]);

        NormaliseFourInPlace
                (
                        on_frustum_directions[x][2],
                        on_frustum_directions[x][3],
                        on_frustum_directions[x][4],
                        on_frustum_directions[x][5]
                );
    }

    for (int i = 0; i < 2; i++) // build axes
    {
        fltx4 *pAxes = &axes[i * 11 + 0];

        FourCrossProducts //TODO: this function uses transpose heavily, should do transposing manually
                (
                        on_frustum_directions[i][0], // viewplane
                        on_frustum_directions[i][2], // left
                        on_frustum_directions[i][2], // up
                        on_frustum_directions[i][4], // right

                        on_frustum_directions[i][1],
                        on_frustum_directions[i][5],
                        on_frustum_directions[i][3],
                        on_frustum_directions[i][3],

                        pAxes[0],
                        pAxes[1],
                        pAxes[2],
                        pAxes[3]
                );

        FourCrossProducts
                (
                        on_frustum_directions[i][4], // down
                        pAxes[1], // cross prod along local Z
                        pAxes[3],
                        pAxes[1],

                        on_frustum_directions[i][5],
                        pAxes[3],
                        pAxes[2],
                        pAxes[2],

                        pAxes[4],
                        pAxes[5],
                        pAxes[6],
                        pAxes[7]
                );

        fltx4 _dummy;

        FourCrossProducts
                (
                        pAxes[1],
                        pAxes[2], // cross prod along local Y
                        pAxes[3],
                        LoadZeroSIMD(),

                        pAxes[4],
                        pAxes[4],
                        pAxes[4],
                        LoadZeroSIMD(),

                        pAxes[8],
                        pAxes[9],
                        pAxes[10],
                        _dummy
                );
    }

    for (int i = 0; i < 22; i++) // project points onto axes, compare sets
    {
        float bounds_frusta[2][2]; // frustum, min/max
        // project starting points
        bounds_frusta[0][0] = bounds_frusta[0][1] = Dot4SIMD2(_pointx4[0][0], axes[i]);
        bounds_frusta[1][0] = bounds_frusta[1][1] = Dot4SIMD2(_pointx4[1][0], axes[i]);

        for (int x = 1; x < 8; x++) {
            //TODO: Implement optimised solution using FourDotProducts function
            float point_frustum_a = Dot4SIMD2(_pointx4[0][x], axes[i]);
            float point_frustum_b = Dot4SIMD2(_pointx4[1][x], axes[i]);

            bounds_frusta[0][0] = Min(bounds_frusta[0][0], point_frustum_a);
            bounds_frusta[0][1] = Max(bounds_frusta[0][1], point_frustum_a);

            bounds_frusta[1][0] = Min(bounds_frusta[1][0], point_frustum_b);
            bounds_frusta[1][1] = Max(bounds_frusta[1][1], point_frustum_b);
        }

        if (bounds_frusta[0][1] < bounds_frusta[1][0] ||
            bounds_frusta[0][0] > bounds_frusta[1][1])
            return true;
    }

    return false;
}

FORCEINLINE void VectorDeviceToSourceSpace(Vector &v) {
    v.Init(-v.z, -v.x, v.y);
}

FORCEINLINE void VectorSourceToDeviceSpace(Vector &v) {
    v.Init(-v.y, v.z, -v.x);
}

FORCEINLINE void MatrixDeviceToSourceSpace(VMatrix &m) {
    Vector x, y, z;
    m.GetBasisVectors(x, y, z);
    m.SetBasisVectors(-z, -x, y);
}

FORCEINLINE void MatrixSourceToDeviceSpace(VMatrix &m) {
    Vector x, y, z;
    m.GetBasisVectors(x, y, z);
    m.SetBasisVectors(-y, z, -x);
}

FORCEINLINE void MatrixSourceToDeviceSpaceInv(VMatrix &m) {
    Vector x, y, z;
    m.GetBasisVectors(x, y, z);
    m.SetBasisVectors(y, -z, x);
}

#endif