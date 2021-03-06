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
    if(m_bstream != NULL) {
#ifdef DEBUG
        //printf("m_bstream is not NULL");
#endif
        return m_bstream[offset];
    }
    else {
#ifdef DEBUG
        //printf("Could not read bit");
        cerr << "Could not read bit" << endl;
#endif
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
#ifdef DEBUG 
    //printf("Starting to read next word\n");
#endif
    if(m_curr_offset+WORDLEN < m_blen) {
        WORD *vtemp;
        vtemp = (WORD*)malloc(sizeof(WORD));

#ifdef DEBUG 
        //printf("after word *\n");
#endif
        for(int i = 0; i < WORDLEN; i++){
            (*vtemp)[i] = _read_bit(m_curr_offset);
#ifdef DEBUG 
            //printf("after read bit\n"); 
#endif
            m_curr_offset++;
        }
#ifdef DEBUG 
        //printf("read the whole WORDLEN\n");
#endif
        return vtemp;
    }
    else {
        WORD* vtemp;
        vtemp = (WORD*)malloc(sizeof(WORD));
        (*vtemp)[0] = 'e';
        (*vtemp)[0] = 'o';
        (*vtemp)[0] = 'f';
        return vtemp;
    }
}

void CBitStream::PrintStream() {
    for(int i = 0; i < m_blen; i++) {
        cout << m_bstream[i];
    }
}
