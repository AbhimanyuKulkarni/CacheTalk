#include "common.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

CBitStream::CBitStream(void) {
    // Init Members
    m_bstream = NULL;
    m_blen = 0;
    m_curr_offset = 0;
}

CBitStream::~CBitStream(void) {
    if(m_bstream != NULL){
        free(m_bstream);
        m_bstream = NULL;
        m_blen = 0;
        m_curr_offset = 0;
    }
}

void CBitStream::_write_bit(char value) {
    if(m_bstream == NULL) {
        m_bstream = (char*)malloc(sizeof(char));
        m_blen = 1;
    }
    else {
        m_blen++;
        m_bstream = (char*)realloc(m_bstream, m_blen*sizeof(char));
    }
    m_bstream[m_blen-1] = value;
}

char CBitStream::_read_bit(int offset) {
    printf("in read bit with offset %d\n",offset);
    if(m_bstream != NULL) {
        printf("m_bstream is not NULL\n");
        printf("m_bstream: %c\n",m_bstream[offset]);
        return m_bstream[offset];
    }
    else {
        printf("Could not read bit\n");
        cerr << "Could not read bit" << endl;
        return 0;
    }
}

void CBitStream::WriteBit(char value) {
    _write_bit(value);
}

char CBitStream::ReadBit(int offset) {
    return _read_bit(offset);
}

void CBitStream::WriteWord(WORD value) {
    for(int i = 0; i < WORDLEN; i++){
        _write_bit(value[i]);
    }
}

WORD* CBitStream::ReadNextWord() {
    printf("Startig to read next word\n");
    if(m_curr_offset+WORDLEN < m_blen) {
        WORD *vtemp;
        vtemp = (WORD*)malloc(sizeof(WORD));
        //*vtemp[0] = '0';

        printf("after word *\n");
        //fflush(stdout);
        for(int i = 0; i < WORDLEN; i++){
            printf("In %d iter and %d\n",i,m_curr_offset);
            (*vtemp)[i] = _read_bit(m_curr_offset);
            printf("after read bit\n");
            //fflush(stdout);
            m_curr_offset++;
        }
        printf("read the whole WORDLEN\n");
        return vtemp;
    }
    else {
        return NULL;
    }
}

void CBitStream::PrintStream() {
    for(int i = 0; i < m_blen; i++) {
        cout << m_bstream[i];
    }
}
