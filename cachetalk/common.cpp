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
        printf("m_bstream is not NULL");
#endif
        return m_bstream[offset];
    }
    else {
#ifdef DEBUG
        printf("Could not read bit");
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
        _write_bit(value.x[i]);
    }
}

WORD CBitStream::ReadNextWord() {

    #ifdef DEBUG 
        printf("Starting to read next word\n");
    #endif

    WORD vtemp;

    if(m_curr_offset+WORDLEN <= m_blen) {    
        for(int i = 0; i < WORDLEN; i++){
            vtemp.x[i] = _read_bit(m_curr_offset);
            m_curr_offset++;
        }
    }
    else {   
        for(int i = 0; i < WORDLEN; i++){
            vtemp.x[i] = 'e';
        }
    }

    return vtemp;
}

void CBitStream::PrintStream() {
    for(int i = 0; i < m_blen; i++) {
        cout << m_bstream[i];
    }
}
