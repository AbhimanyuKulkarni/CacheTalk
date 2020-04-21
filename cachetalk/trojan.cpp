#include "trojan.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream> 
#include <math.h>

using namespace std;

Trojan::Trojan(void) {
    m_tset = 0;
    CBitStream m_data_stream = CBitStream();
    CBitStream m_trans_stream = CBitStream();
    int sizes[8] = {8, 16, 20, 24, 34, 36, 40, 64};
}

Trojan::~Trojan(void) {
    
}

void Trojan::GenStream(int n) {
    for(int i = 0; i < n; i++) {
        WORD value;
        for(int j = 0; j < WORDLEN; j++) {
            char randbit = (char) rand()%2;
            value[j] = randbit;
        }
        m_data_stream.WriteWord(value);
    }
    printf("Target Stream generated by Trojan as follows: ");
    m_data_stream.PrintStream();
}

WORD* Trojan::GetData() {
    m_curr_data = m_data_stream.ReadNextWord();

    if(m_curr_data == NULL){
        return NULL;
    }

    m_curr_size_idx = 0;
    for(int i = 0; i < WORDLEN; i++){
        if(m_curr_data[i] == "1") {
            m_curr_size_idx += pow(2,WORDLEN-i-1);
        }
    }
    printf("Trojan: Sending data = ");
    for(int i = 0; i < WORDLEN; i++) {
        cout << m_curr_data[i];
    }
    return m_curr_data;
}

void Trojan::SetTargetSet(long set) {
    m_tset = set;
}

void Trojan::AccessSet() {
    int size = sizes[m_curr_size_idx];
    PrimeSetWithSize(m_tset, size);
}

void Trojan::TransmissionAck() {
    m_trans_stream.WriteWord(*m_curr_data);
}