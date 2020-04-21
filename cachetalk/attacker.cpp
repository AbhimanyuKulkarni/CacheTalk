#include "attacker.h"

void flush(){
    FlushSet(tset);
}

void trojan_access() {
    trojan.AccessSet();
}

void init_trojan() {
    trojan.SetTargetSet(tset);
    trojan.GenStream(100);
    WORD* first_data = trojan.GetData();
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
}

void init_spy() {
    spy.SetTargetSet(tset);
}

void run_channel() {
    int done = 0;

    while(!done) {
        int temp_size;
        temp_size = spy.GetSize(&trojan_access, &flush);
        spy.DecryptData(temp_size);
        done = ack_to_trojan();
    }
}

int main (int argc, char *argv[]){
    init_spy();
    init_trojan();
    run_channel();
    transmission_complete();
}