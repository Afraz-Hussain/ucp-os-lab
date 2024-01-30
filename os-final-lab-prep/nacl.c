#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t naSem, clSem, saltSem;

void makeSalt() {
    printf("Salt (NaCl) is produced!\n");
}

void NReady() {
    sem_wait(&naSem);
    sem_post(&saltSem); // Signal that Na is ready
    sem_wait(&clSem);   // Wait for Cl to be ready
    makeSalt();
    sem_post(&naSem);   // Signal that Na has finished
}

void CReady() {
    sem_wait(&clSem);
    sem_post(&saltSem); // Signal that Cl is ready
    sem_wait(&naSem);   // Wait for Na to be ready
    makeSalt();
    sem_post(&clSem);   // Signal that Cl has finished
}

int main() {
    sem_init(&naSem, 0, 1);  // Initialize semaphore for Na
    sem_init(&clSem, 0, 1);  // Initialize semaphore for Cl
    sem_init(&saltSem, 0, 0);  // Initialize semaphore for salt

    pthread_t naThread, clThread;

    pthread_create(&naThread, NULL, (void*)NReady, NULL);
    pthread_create(&clThread, NULL, (void*)CReady, NULL);

    pthread_join(naThread, NULL);
    pthread_join(clThread, NULL);

    return 0;
}
