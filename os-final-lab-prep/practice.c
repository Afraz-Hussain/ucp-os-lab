#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
sem_t x,y;
pthread_t tid;
pthread_t writerthread[100],readerthread[100];
int readercount=0;
void *writer(void *param){
    sem_wait (&x);
    readercount++;
    if(readercount==1){
        sem_wait(&y);
    }
    sem_post(&x);
    printf("%d reader entring .../n",readercount);
    usleep(3);
    if(readercount==0)
 sem_wait(&y);
 sem_post(&x);
 printf("Reader is leaving...\n",readercount+1);

 

}
//javascript   <->4months-1 year
//Java for cp & projects<->1 year +
//oop,data structure basics like arrays,stack,queues,linkedlist,graphs

//algorithms
// 
/*

bellman ford
dijistra
kruskal



*/

#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
sem_t room;
sem_t chopstick[5];
void *philosopher(void*);
void eat();
int main()
{
    int i,a[5];
    pthread_t tid[5];
    sem_init(&room,4);
    for(i=0;i<5;i++){
        sem_init(&chopstick[i],0,1);
    }
for(i=0;i<5;i++){
        pthread_create(&tid[i],NULL,philosopher,(void*)&a[i]);
    }
for(i=0;i<5;i++){
    pthread_join(tid[i],NULL);
}
}
void *philosopher(void *num){
    int phil=*(int *)num;
    sem_wait(&room);
    printf("%d Philosopher has entered the room..",phil);
    sem_wait(&chopstick[phil]);
    sem_wait(&chopstick[(phil+1)]%5);
    eat(phil);
    sleep(2);
    printf("philosopher has finished eating\n",phil);
    sem_post(&chopstick[(phil+1)]%5);
    sem_post(&chopstick[phil]);
    sem_post(&room);
}

sem_t hydro,oxy;
int WaterMolecule=0;
int Hydrogen=0;
int Oxygen=0;
void makeWater(){
   
    Hydrogen-=2;
    Oxygen-=1;
 WaterMolecule++;
 printf("water molecules created%d\n",WaterMolecule);
}
void *HReady(void *ptr){
for(unsigned int i=0;i<1000;i++){
 
    sem_wait(&hydro);
    if(Hydrogen>=2&&Oxygen>=1){
        makeWater();
        ++Hydrogen;
        
    }
sem_post(&oxy);
}
pthread_exit(0);
}
void *oReady(void *param){
    for(unsigned int i=0;i<1000;i++){
        sem_wait(&oxy);
         
            ++Oxygen;
        if(Hydrogen>=2){
           makeWater();
        }
         sem_post(&hydro);
    }
   pthread_exit(0);
}
int main()
{
   pthread_t pid1, pid2;
    sem_init(&hydro, 0, 2);
    sem_init(&oxy, 0, 0);
    pthread_create(&pid1, NULL, &hReady, NULL);
    pthread_create(&pid2, NULL, &oReady, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
}



