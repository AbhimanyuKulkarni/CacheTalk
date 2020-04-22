/* Considerations:  lock = 1 -> Spy is active
                    lock = 2 -> Trojan active and runs trojan.AccessSet()
                    lock = 3 -> Trojan active and runs Acknowledgement protocol */

#include "mt_attacker.h"
#include <pthread.h>

pthread_mutex_t lock;
int covid = 19;

void flush(){
    FlushSet(tset);
}

void trojan_access() {
    /* Set the lock value to 2 and wait for it to come back to 1 */
    covid = 2;
    pthread_mutex_unlock(&lock);
    pthread_mutex_lock(&lock);
}

void ack_to_trojan() {
    /* Set the lock value to 3 and wait for it to come back to 1 */
    covid = 3;
    pthread_mutex_unlock(&lock);
    pthread_mutex_lock(&lock);
    
}

void *spy_wrapper(void *arg) {

#ifdef DEBUG
    printf("In spy wrapper\n");
#endif
    Spy spy;
    
    // Spy Init Phase
    spy.SetTargetSet(tset);

    // Main Operation
    int done = 0;
    while(!done) {
        pthread_mutex_lock(&lock);
        int temp_size;
        temp_size = spy.GetSize(&trojan_access, &flush);
        spy.DecryptData(temp_size);
        ack_to_trojan();
        pthread_mutex_unlock(&lock);
        /* How to update the "done" variable? */
    }

}

void *trojan_wrapper(void *arg) {

    Trojan trojan;
#ifdef DEBUG
    printf("In trojan wrapper\n");
#endif
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
        pthread_mutex_lock(&lock);
        //while(/*Wait to acquire lock*/);
        if(covid == 2) {
            trojan.AccessSet();
        }
        else if(covid == 3) {
            trojan.TransmissionAck();
            WORD* nxt_data = trojan.GetData();
            if(nxt_data == NULL) {
                done = 1;
            }
            done = 0;
        }
        /* Here -> Set the lock value back to 0, i.e. release the lock*/
        covid = 1;
        pthread_mutex_unlock(&lock);
    }

    // Here -> Somehow pass the information out to Spy that trojan is done.

}

int main (int argc, char *argv[]){

    
    if(pthread_mutex_init(&lock, NULL) != 0){
        printf("Mutex init has failed\n");
        return 1;
    }
    // Create Spy and Trojan threads running their respective wrapper functions
    pthread_t spy_tid, trojan_tid;
    int create_spy, create_trojan, join_spy, join_trojan;
    create_spy = pthread_create(&spy_tid, NULL, &spy_wrapper, NULL);
    if(create_spy){
#ifdef DEBUG
        printf("Error creating spy thread\n");
#endif
    }
    create_trojan = pthread_create(&trojan_tid, NULL, &trojan_wrapper, NULL);
    if(create_trojan){
#ifdef DEBUG
        printf("Error creating trojan thread\n");
#endif
    }

    join_spy = pthread_join(spy_tid, NULL);
    if(join_spy){
#ifdef DEBUG
        printf("Error joining spy thread\n");
#endif
    }
    join_trojan = pthread_join(trojan_tid, NULL);
    if(trojan_tid){
#ifdef DEBUG
        printf("Error joining trojan thread\n");
#endif
    }

    return 0;
}
