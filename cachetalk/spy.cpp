#include "spy.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int compare(const void *ap, const void *bp)
{
    const int *a = (int *) ap;
    const int *b = (int *) bp;
    if(*a < *b)
        return -1;
    else if(*a > *b)
        return 1;
    else
        return 0;
}

Spy::Spy(void) {
    m_tset = 0;
    CBitStream m_rec_stream = CBitStream();
    int sizes[8] = {8, 16, 20, 24, 34, 36, 40, 64};
}

Spy::~Spy(void) {

}

void Spy::SetTargetSet(long set) {
    m_tset = set;
}

int Spy::GetSize(void(*CallTrojan)(), void(*flush)()) {
    int res_size = get_size(m_tset, CallTrojan, flush);
    return res_size;
}

WORD* Spy::DecryptData(int size) {
    WORD* vtemp;
    int size_idx = *((int*) bsearch(&size, &sizes, 8, sizeof(int), compare));
    int tmp_idx = size_idx;
    for(int i = 0; i < WORDLEN; i++) {
        *vtemp[i] = tmp_idx%2;
        tmp_idx = tmp_idx/2;
    }
    m_rec_stream.WriteWord(*vtemp);
    printf("Spy: Received data = ");
    for(int i = 0; i < WORDLEN; i++) {
        cout << vtemp[i];
    }
    return vtemp;
}

