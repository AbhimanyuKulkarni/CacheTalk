//ECE 757 CacheTalk Project Code
//Wrapper file for trojan and spy
//Authors: Abhimanyu Kulkarni and Shivangi Kamat
//Adapted from cc_artifact_evaluation code base

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <semaphore.h>
#include "header.h"
//Defines
#define WORDLEN 3
#define SET 2
#define LINESIZE 64

sem_t mutex;


int main (int argc, char *argv[]){
    //Wrapper function initializes the spy and trojan
    sem_init(&mutex,1,1);
    //1- semaphore will be shared with the forked processes
    //1- inital value of semaphore
   
    int test = 100;
    pthread_t spy_tid, trojan_tid;
    int create_spy, create_trojan;
    int join_spy, join_trojan;
    //create spy
    create_spy = pthread_create(&spy_tid, NULL, spy, test); 
    if(create_spy) printf("Error creating spy thread\n");
    create_trojan = pthread_create(&trojan_tid, NULL, trojan, test); 
    if(create_trojan) printf("Error creating trojan thread\n");

    join_spy = pthread_join(spy_tid, NULL);
    if(join_spy) printf("Error joining spy thread\n");
    join_trojan = pthread_join(trojan_tid, NULL);
    if(join_trojan) printf("Error joining trojan thread\n");
    printf("OKAY, BYE!\n");

    return 0;

}
