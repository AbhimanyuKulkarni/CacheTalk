//ECE 757 CacheTalk Project Code
//Trojan establishes covert channel with the spy.
//Accesses secret data (3-bits at a time, depending on the compression) 
//and communicates with the spy
//Authors: Shivangi Kamat and Abhimanyu Kulkarni
//Adapted from cc_artifact_evaluation

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void * trojan(void * arg){
    printf("In trojan\n");

    return 0;
}
