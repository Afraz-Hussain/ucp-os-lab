#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

int turn = 0; // Indicates whose turn it is to enter the critical section
int flag[NUM_THREADS]; // Indicates if a thread wants to enter the critical section

void enter_critical_section(int thread_id) {
    int other = 1 - thread_id; // Index of the other thread

    flag[thread_id] = 1; // Mark that the current thread wants to enter the critical section
    turn = other; // Give the other thread a chance to enter

    // Wait while the other thread is in the critical section and it's not our turn
    while (flag[other] == 1 && turn == other) {
        // Busy-wait
    }
}

void exit_critical_section(int thread_id) {
    flag[thread_id] = 0; // Mark that the current thread has finished in the critical section
}

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    for (int i = 0; i < 5; ++i) {
        enter_critical_section(thread_id);

        // Critical section
        printf("Thread %d is in the critical section\n", thread_id);
        fflush(stdout);

        exit_critical_section(thread_id);

        // Non-critical section
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1};

    // Initialize flags
    flag[0] = 0;
    flag[1] = 0;

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
