/* Considerations:  lock = 0 -> Spy is active
                    lock = 1 -> Trojan active and runs trojan.AccessSet()
                    lock = 2 -> Trojan active and runs Acknowledgement protocol */

#include "mt_attacker.h"

void flush(){
    FlushSet(tset);
}

void trojan_access() {
    /* Set the lock value to 1 and wait for it to come back to 0 */
}

void ack_to_trojan() {
    /* Set the lock value to 2 and wait for it to come back to 0 */
}

void spy_wrapper() {

    Spy spy;

    // Spy Init Phase
    spy.SetTargetSet(tset);

    // Main Operation
    int done = 0;
    while(!done) {
        int temp_size;
        temp_size = spy.GetSize(&trojan_access, &flush);
        spy.DecryptData(temp_size);
        ack_to_trojan();
        /* How to update the "done" variable? */
    }

}

void trojan_wrapper() {

    Trojan trojan;

    // Trojan Init Phase
    trojan.SetTargetSet(tset);
    trojan.GenStream(100);
    WORD* first_data = trojan.GetData();
    if(first_data == NULL) {
        cerr << "Target Stream not generated! Please Check Trojan Initialization." << endl;
    }

    // Main Operation
    int done = 0;
    while(!done) {
        while(/*Wait to acquire lock*/);
        if(/*lock value is 1*/) {
            trojan.AccessSet();
        }
        else if(/*lock value is 2*/) {
            trojan.TransmissionAck();
            WORD* nxt_data = trojan.GetData();
            if(nxt_data == NULL) {
                done = 1;
            }
            done = 0;
        }
        /* Here -> Set the lock value back to 0, i.e. release the lock*/
    }

    // Here -> Somehow pass the information out to Spy that trojan is done.

}

int main (int argc, char *argv[]){

    // Create Spy and Trojan threads running their respective wrapper functions

}
