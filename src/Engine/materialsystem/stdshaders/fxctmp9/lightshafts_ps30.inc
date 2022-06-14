#include "shaderlib/cshader.h"

class lightshafts_ps30_Static_Index {
private:
    int m_nFLASHLIGHTDEPTHFILTERMODE;
#ifdef _DEBUG
    bool m_bFLASHLIGHTDEPTHFILTERMODE;
#endif
public:
    void SetFLASHLIGHTDEPTHFILTERMODE(int i) {
        Assert(i >= 0 && i <= 2);
        m_nFLASHLIGHTDEPTHFILTERMODE = i;
#ifdef _DEBUG
        m_bFLASHLIGHTDEPTHFILTERMODE = true;
#endif
    }

    void SetFLASHLIGHTDEPTHFILTERMODE(bool i) {
        m_nFLASHLIGHTDEPTHFILTERMODE = i ? 1 : 0;
#ifdef _DEBUG
        m_bFLASHLIGHTDEPTHFILTERMODE = true;
#endif
    }

public:
    lightshafts_ps30_Static_Index() {
#ifdef _DEBUG
        m_bFLASHLIGHTDEPTHFILTERMODE = false;
#endif // _DEBUG
        m_nFLASHLIGHTDEPTHFILTERMODE = 0;
    }

    int GetIndex() {
        // Asserts to make sure that we aren't using any skipped combinations.
        // Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
        bool bAllStaticVarsDefined = m_bFLASHLIGHTDEPTHFILTERMODE;
        Assert( bAllStaticVarsDefined );
#endif // _DEBUG
        return (8 * m_nFLASHLIGHTDEPTHFILTERMODE) + 0;
    }
};

#define shaderStaticTest_lightshafts_ps30 psh_forgot_to_set_static_FLASHLIGHTDEPTHFILTERMODE + 0

class lightshafts_ps30_Dynamic_Index {
private:
    int m_nFLASHLIGHTSHADOWS;
#ifdef _DEBUG
    bool m_bFLASHLIGHTSHADOWS;
#endif
public:
    void SetFLASHLIGHTSHADOWS(int i) {
        Assert(i >= 0 && i <= 1);
        m_nFLASHLIGHTSHADOWS = i;
#ifdef _DEBUG
        m_bFLASHLIGHTSHADOWS = true;
#endif
    }

    void SetFLASHLIGHTSHADOWS(bool i) {
        m_nFLASHLIGHTSHADOWS = i ? 1 : 0;
#ifdef _DEBUG
        m_bFLASHLIGHTSHADOWS = true;
#endif
    }

private:
    int m_nUBERLIGHT;
#ifdef _DEBUG
    bool m_bUBERLIGHT;
#endif
public:
    void SetUBERLIGHT(int i) {
        Assert(i >= 0 && i <= 1);
        m_nUBERLIGHT = i;
#ifdef _DEBUG
        m_bUBERLIGHT = true;
#endif
    }

    void SetUBERLIGHT(bool i) {
        m_nUBERLIGHT = i ? 1 : 0;
#ifdef _DEBUG
        m_bUBERLIGHT = true;
#endif
    }

private:
    int m_nDEPTHBLEND;
#ifdef _DEBUG
    bool m_bDEPTHBLEND;
#endif
public:
    void SetDEPTHBLEND(int i) {
        Assert(i >= 0 && i <= 1);
        m_nDEPTHBLEND = i;
#ifdef _DEBUG
        m_bDEPTHBLEND = true;
#endif
    }

    void SetDEPTHBLEND(bool i) {
        m_nDEPTHBLEND = i ? 1 : 0;
#ifdef _DEBUG
        m_bDEPTHBLEND = true;
#endif
    }

public:
    lightshafts_ps30_Dynamic_Index() {
#ifdef _DEBUG
        m_bFLASHLIGHTSHADOWS = false;
#endif // _DEBUG
        m_nFLASHLIGHTSHADOWS = 0;
#ifdef _DEBUG
        m_bUBERLIGHT = false;
#endif // _DEBUG
        m_nUBERLIGHT = 0;
#ifdef _DEBUG
        m_bDEPTHBLEND = false;
#endif // _DEBUG
        m_nDEPTHBLEND = 0;
    }

    int GetIndex() {
        // Asserts to make sure that we aren't using any skipped combinations.
        // Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
        bool bAllDynamicVarsDefined = m_bFLASHLIGHTSHADOWS && m_bUBERLIGHT && m_bDEPTHBLEND;
        Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
        return (1 * m_nFLASHLIGHTSHADOWS) + (2 * m_nUBERLIGHT) + (4 * m_nDEPTHBLEND) + 0;
    }
};

#define shaderDynamicTest_lightshafts_ps30 psh_forgot_to_set_dynamic_FLASHLIGHTSHADOWS + psh_forgot_to_set_dynamic_UBERLIGHT + psh_forgot_to_set_dynamic_DEPTHBLEND + 0
