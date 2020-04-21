#include "attacker.h"

void flush(){
    FlushSet(tset);
}

void trojan_access() {
    trojan.AccessSet();
}

void init_trojan() {
    //printf("In trojan\n");
    //fflush(stdout);
    trojan.SetTargetSet(tset);
    //printf("Trojan: set target set\n");
    //fflush(stdout);
    trojan.GenStream(100);
    //printf("Trojan: gen stream\n");
    //fflush(stdout);
    WORD* first_data = trojan.GetData();
    //printf("Trojan: first data\n");
    //fflush(stdout);
    if(first_data == NULL) {
        cerr << "Target Stream not generated! Please Check Trojan Initialization." << endl;
    }
}

int ack_to_trojan() {
    trojan.TransmissionAck();
    WORD* nxt_data = trojan.GetData();
    if(nxt_data == NULL) {
        return 1;
    }
    return 0;
}

void transmission_complete(){
    // Somehow compare transmitted and received streams
    printf("Transmission Completed");
    //fflush(stdout);
}

void init_spy() {
    spy.SetTargetSet(tset);
}

void run_channel() {
    int done = 0;

    while(!done) {
        int temp_size;
        temp_size = spy.GetSize(&trojan_access, &flush);
        printf("temp size: %d\n",temp_size);
        spy.DecryptData(temp_size);
        done = ack_to_trojan();
    }
}

int main (int argc, char *argv[]){
    init_spy();
    //printf("after init spy\n");
    //fflush(stdout);
    init_trojan();
    //printf("after init trojan\n");
    //fflush(stdout);
    run_channel();
    //printf("after run channel\n");
    //fflush(stdout);
    transmission_complete();
    //printf("after transaction complete\n");
    //fflush(stdout);
}
