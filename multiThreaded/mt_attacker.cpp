/* Considerations:  lock = 1 -> Spy is active
                    lock = 2 -> Trojan active and runs trojan.AccessSet()
                    lock = 3 -> Trojan active and runs Acknowledgement protocol
                    lock = 4 -> Transmission is done and both threads should finish */

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
    #ifdef DEBUG
        printf("Spy: Init Done\n");
    #endif
    // Main Operation
    int done = 0;
    int loop_cnt = 0;
    while(loop_cnt < 5) {
        #ifdef DEBUG
            printf("Spy inside loop count = %d\n", loop_cnt);
        #endif
        pthread_mutex_lock(&lock);
        #ifdef DEBUG
            printf("Spy Lock acquired with covid = %d\n", covid);
        #endif
        if(covid = 1) {
            #ifdef DEBUG
                printf("Spy Running Channel inside loop count = %d \n", loop_cnt);
            #endif
            int temp_size;
            #ifdef DEBUG
                printf("Spy Going into GetSize loop count = %d \n", loop_cnt);
            #endif
            temp_size = spy.GetSize(&trojan_access, &flush);
            #ifdef DEBUG
                printf("Spy Size detected = %d inside loop count = %d \n", temp_size, loop_cnt);
                printf("Spy Going into Decrypt data\n");
            #endif
            spy.DecryptData(temp_size);
            #ifdef DEBUG
                printf("Spy Decrypted, Going into ack to trojan loop count = %d \n", loop_cnt);
            #endif
            ack_to_trojan();
        }
        else if(covid = 4) {
            #ifdef DEBUG
                printf("Spy Done recieved loop count = %d \n", loop_cnt);
            #endif
            done = 1;
        }
        pthread_mutex_unlock(&lock);
        #ifdef DEBUG
            printf("Spy Unlocked \n");
        #endif
        /* How to update the "done" variable? */
        loop_cnt++;
    }

}

void *trojan_wrapper(void *arg) {

    Trojan trojan;
    #ifdef DEBUG
        printf("In trojan wrapper\n");
    #endif
    // Trojan Init Phase
    trojan.SetTargetSet(tset);
    trojan.GenStream(5);
    WORD* first_data = trojan.GetData();
    if(first_data == NULL) {
        cerr << "Target Stream not generated! Please Check Trojan Initialization." << endl;
    }
    #ifdef DEBUG
        printf("Trojan: Init Done\n");
    #endif

    // Main Operation
    int done = 0;
    int loop_cnt = 0;
    while(loop_cnt < 30) {
        #ifdef DEBUG
            printf("Trojan inside loop count = %d\n", loop_cnt);
        #endif
        pthread_mutex_lock(&lock);
        #ifdef DEBUG
            printf("Trojan Lock acquired with covid = %d\n", covid);
        #endif
        //while(/*Wait to acquire lock*/);
        if(covid == 2) {
            #ifdef DEBUG
                printf("Trojan Access Set\n");
            #endif
            trojan.AccessSet();
            covid = 1;
        }
        else if(covid == 3) {
            #ifdef DEBUG
                printf("Trojan Ack to trojan --> \n");
            #endif
            trojan.TransmissionAck();
            WORD* nxt_data = trojan.GetData();
            if(*nxt_data[0] == 'e') {
                #ifdef DEBUG
                    printf("EOF recieved\n");
                #endif
                done = 1;
                covid = 4;
            }
            else {
                #ifdef DEBUG
                    printf("Next data recieved = ");
                    for(int i = 0; i < WORDLEN; i++) {
                        cout << nxt_data[i];
                    }
                    cout << endl;
                #endif
                covid = 1;
            }
        }
        /* Here -> Set the lock value back to 0, i.e. release the lock*/
        pthread_mutex_unlock(&lock);
        #ifdef DEBUG
            printf("Trojan unlocked!");
        #endif
        loop_cnt++;
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
