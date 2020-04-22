#ifndef _COMMON_H
#define _COMMON_H

#define WORDLEN 3
//#define DEBUG

#include "../common/cache_manipulation.h"
#include "../common/constants.h"
#include "../common/patterns.h"
#include "../common/rdtsc.h"

typedef char WORD[WORDLEN];  
class CBitStream {
public:
    // Public Methods
    CBitStream(void);
    virtual ~CBitStream(void);
    void WriteBit(char value);
    char ReadBit(int offset);
    void WriteWord(WORD value);
    WORD* ReadNextWord();
    void PrintStream();
private:
    // Private Methods
    void _write_bit(char value);
    char _read_bit(int offset);
private:
    // Private Members
    char* m_bstream;
    int m_blen;
    int m_curr_offset;
};

#endif
