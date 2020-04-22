#include "attacker.h"

void flush(){
    FlushSet(tset);
}

void trojan_access() {
    trojan.AccessSet();
}

void init_trojan() {
#ifdef DEBUG
    printf("Attacker: Init trojan\n");
#endif
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
    printf("Transmission Completed\n");
}

void init_spy() {
    spy.SetTargetSet(tset);
}

void run_channel() {
    int done = 0;

    while(!done) {
        int temp_size;
        temp_size = spy.GetSize(&trojan_access, &flush);
#ifdef DEBUG 
        printf("temp size: %d\n",temp_size);
#endif
        spy.DecryptData(temp_size);
        done = ack_to_trojan();
    }
}

int main (int argc, char *argv[]){
    init_spy();
#ifdef DEBUG 
    printf("Attacker: After init spy\n");
#endif
    init_trojan();
#ifdef DEBUG 
    printf("Attacker: After init trojan\n");
#endif
    run_channel();
#ifdef DEBUG 
    printf("Attacker: After run channel\n");
#endif
    transmission_complete();
#ifdef DEBUG 
    printf("Attacker: After transaction complete\n");
#endif
}
