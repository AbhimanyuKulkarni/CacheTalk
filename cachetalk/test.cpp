#include <stdlib.h>
#include <stdio.h>
#include <iostream> 
using namespace std;

typedef struct WORD {char x[3];} WORD;  
WORD a;

WORD* fn() {
    a = {'0','1','0'};
    return &a;
}

int main(int argc, char* argv[]) {

    WORD* b = fn();
    WORD p = *b;
    int i = 0;
    cout << p.x[i] << endl;
    ++i;
    cout << p.x[i] << endl;
    
}