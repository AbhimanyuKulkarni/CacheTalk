#ifndef _COMMON_H
#include "common.h"
#endif


class Spy{
public:
    // Public Methods
    Spy(void);
    virtual ~Spy(void);
    void SetTargetSet(long set);
    int GetSize(void(*CallTrojan)(), void(*flush)());
    WORD DecryptData(int size);

public:
    // Public Members
    CBitStream m_rec_stream;
    long m_tset;
    const int sizes[8] = {8, 16, 20, 24, 34, 36, 40, 64};
};
