#ifndef _COMMON_H
#include "common.h"
#endif
class Trojan {
public:
    // Public Methods
    Trojan(void);
    virtual ~Trojan(void);
    void GenStream(int n);
    WORD* GetData();
    void SetTargetSet(long set);
    void AccessSet();
    void TransmissionAck(); 
public:
    // Public Members
    long m_tset;
    CBitStream m_data_stream;
    CBitStream m_trans_stream;
    WORD* m_curr_data;
    int m_curr_size_idx;
    const int sizes[8] = {8, 16, 20, 24, 34, 36, 40, 64};
};
