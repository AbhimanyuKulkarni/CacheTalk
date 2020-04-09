#include "common.h"
#include "../common/constants.h"
#include "../common/cache_manipulation.h"
#include "../common/patterns.h"
#include "../common/rdtsc.h"

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
    int sizes[8];
};
