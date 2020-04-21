#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

sem_t mutex;

void main (int argc, char * argv[]){
    sem_init(&mutex,0,1) 
    //0- semaphore will not be shared with the forked processes
    //1- inital value of semaphore

}
