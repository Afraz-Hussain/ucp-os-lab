#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

int WaterMolecule = 0;
int Hydrogen = 0;
int Oxygen = 0;

sem_t hydro, oxy;

void makeWater() {
    Hydrogen -= 2;
    Oxygen -= 1;
    WaterMolecule++;
    printf("Water Molecule Produced: %d\n", WaterMolecule);
}

void* hReady(void* ptr) {
    for (unsigned int i = 0; i < 1000; i++) {
        sem_wait(&hydro);
        ++Hydrogen;
        if (Hydrogen >= 2 && Oxygen >= 1)
            makeWater();
        sem_post(&oxy);
    }
    pthread_exit(0);
}

void* oReady(void* ptr) {
    for (unsigned int i = 0; i < 1000; i++) {
        sem_wait(&oxy);
        ++Oxygen;
        if (Hydrogen >= 2)
            makeWater();
        sem_post(&hydro);
    }
    pthread_exit(0);
}

int main() {
    pthread_t pid1, pid2;
    sem_init(&hydro, 0, 2);
    sem_init(&oxy, 0, 0);
    pthread_create(&pid1, NULL, &hReady, NULL);
    pthread_create(&pid2, NULL, &oReady, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    return 0;
}



#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

sem_t hydro,oxy;
int WaterMolecule=0;
int Hydrogen=0;
int Oxygen=0;


void makeWater()
{
Hydrogen-=2;
Oxygen-=1;
WaterMolecule++;
printf("Water molecule formed %d\n",WaterMolecule);
}

void hReady(void *ptr){
    for(unsigned int i=0;i<1000;i++){
sem_wait(&hydro);
++Hydrogen;
if(Hydrogen>=2&&Oxygen>=1){
        makeWater();
    }
    sem_post(&oxy);
    } 
pthread_exit(0);
}


void oReady(void *ptr){
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
    pthread_t pid1,pid2;
    sem_init(&hydro,0,1);
    sem_init(&oxy,0,0);
    pthread_create(&pid1,NULL,&hReady,NULL);
    pthread_create(&pid2,NULL,oReady,NULL);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
}
