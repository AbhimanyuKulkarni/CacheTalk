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
    trojan.GenStream(10);
    WORD first_data = trojan.GetData();
    if(first_data.x[0] == 'e') {
        cerr << "Target Stream not generated! Please Check Trojan Initialization." << endl;
    }
}

int ack_to_trojan() {
    trojan.TransmissionAck();
    WORD nxt_data = trojan.GetData();
    if(nxt_data.x[0] == 'e') {
        return 1;
    }
    return 0;
}

void transmission_complete(){
    // Somehow compare transmitted and received streams
    printf("Transmission Completed\n");
    printf("Transmitted Stream: ");
    trojan.m_trans_stream.PrintStream();
    printf("\nReceived Stream: ");
    spy.m_rec_stream.PrintStream();
    cout << endl;
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

    setbuf(stdout, NULL);

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
