#include "spy.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int compare(const void *ap, const void *bp)
{
#ifdef DEBUG
    printf("In compare\n");
#endif
    const int *a = (int *) ap;
    const int *b = (int *) bp;
#ifdef DEBUG
    printf("*a is %d, *b is %d\n",*a, *b);
#endif
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
    vtemp = (WORD*)malloc(sizeof(WORD));
    int size_idx = *((int*) bsearch(&size, &sizes, 8, sizeof(int), compare));
    int tmp_idx = size_idx;
    for(int i = 0; i < WORDLEN; i++) {
        *vtemp[i] = tmp_idx%2;
        tmp_idx = tmp_idx/2;
    }
    m_rec_stream.WriteWord(*vtemp);
#ifdef DEBUG
    printf("Spy: Received data = ");
    for(int i = 0; i < WORDLEN; i++) {
        cout << vtemp[i];
    }
#endif
    return vtemp;
}

