#include "shaderlib/cshader.h"

class pp_fog_vs20_Static_Index {
public:
    pp_fog_vs20_Static_Index() {
    }

    int GetIndex() {
        // Asserts to make sure that we aren't using any skipped combinations.
        // Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
#endif // _DEBUG
        return 0;
    }
};

#define shaderStaticTest_pp_fog_vs20 0

class pp_fog_vs20_Dynamic_Index {
private:
    int m_nSKINNING;
#ifdef _DEBUG
    bool m_bSKINNING;
#endif
public:
    void SetSKINNING(int i) {
        Assert(i >= 0 && i <= 1);
        m_nSKINNING = i;
#ifdef _DEBUG
        m_bSKINNING = true;
#endif
    }

    void SetSKINNING(bool i) {
        m_nSKINNING = i ? 1 : 0;
#ifdef _DEBUG
        m_bSKINNING = true;
#endif
    }

public:
    pp_fog_vs20_Dynamic_Index() {
#ifdef _DEBUG
        m_bSKINNING = false;
#endif // _DEBUG
        m_nSKINNING = 0;
    }

    int GetIndex() {
        // Asserts to make sure that we aren't using any skipped combinations.
        // Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
        bool bAllDynamicVarsDefined = m_bSKINNING;
        Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
        return (1 * m_nSKINNING) + 0;
    }
};

#define shaderDynamicTest_pp_fog_vs20 vsh_forgot_to_set_dynamic_SKINNING + 0
