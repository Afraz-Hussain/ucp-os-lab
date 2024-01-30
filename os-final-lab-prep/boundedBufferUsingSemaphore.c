#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <semaphore.h>

sem_t full,empty;    
int n=10; int buffer[10];
int in=0, out=0; 

void* producer (void* ptr)
{
 for(unsigned int i=1;i<8;i++)
 {
  sem_wait(&empty);
  buffer[in]=i;
  in=(in+1)%n; 
  sem_post(&full);
 }  
 
 pthread_exit(0);
}

void* consumer (void* ptr)
{
 pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
 
 for(unsigned int i=1;i<8;i++)
 {
  sem_wait(&full); /* check if there is new data*/
  printf("%d\n",buffer[out]); /*print that data*/
  
 
  out=(out+1)%n; /*increment counter */
  sem_post(&empty); /* create vacancy */
  
 
 }
 pthread_exit(0); 
}
int main()
{
pthread_t pid1,pid2; 
sem_init(&full, 0, 0); /*initializing semaphore variable with
0*/
sem_init(&empty, 0, 10); /*initializing semaphore variable
with 10*/
pthread_create(&pid2,NULL,&consumer,NULL); 
pthread_create(&pid1,NULL,&producer,NULL);
pthread_join(pid1,NULL);
pthread_join(pid2,NULL);
return 0;
} 