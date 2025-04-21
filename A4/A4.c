#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 5

int data = 0;
int readerCount = 0;
sem_t x, y;

void* reader_sync(void* arg) {
    int id = *((int*)arg);

    sem_wait(&x);
    readerCount++;
    if (readerCount == 1)
        sem_wait(&y);
    sem_post(&x);

    printf("Reader %d is reading data: %d\n", id, data);
    sleep(1);

    sem_wait(&x);
    readerCount--;
    if (readerCount == 0)
        sem_post(&y);
    sem_post(&x);

    printf("Reader %d is done reading.\n", id);
    return NULL;
}

void* writer_sync(void* arg) {
    int id = *((int*)arg);

    printf("Writer %d is trying to enter...\n", id);
    sem_wait(&y);

    data++;
    printf("Writer %d modified data to: %d\n", id, data);
    sleep(1);

    printf("Writer %d is leaving...\n", id);
    sem_post(&y);
    return NULL;
}

void* reader_nosync(void* arg) {
    int id = *((int*)arg);

    readerCount++;
    printf("Reader %d is reading data: %d\n", id, data);
    sleep(1);
    readerCount--;
    printf("Reader %d is done reading.\n", id);
    return NULL;
}

void* writer_nosync(void* arg) {
    int id = *((int*)arg);

    data++;
    printf("Writer %d modified data to: %d\n", id, data);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[2];
    int readerIds[MAX_READERS], writerIds[2];
    int choice;

    printf("1. Readers-Writers WITHOUT Synchronization\n");
    printf("2. Readers-Writers WITH Synchronization\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 2) {
        sem_init(&x, 0, 1);
        sem_init(&y, 0, 1);
    }

    // Create reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        readerIds[i] = i + 1;
        if (choice == 1)
            pthread_create(&readers[i], NULL, reader_nosync, &readerIds[i]);
        else
            pthread_create(&readers[i], NULL, reader_sync, &readerIds[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        writerIds[i] = i + 1;
        if (choice == 1)
            pthread_create(&writers[i], NULL, writer_nosync, &writerIds[i]);
        else
            pthread_create(&writers[i], NULL, writer_sync, &writerIds[i]);
    }

    // Join reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    if (choice == 2) {
        sem_destroy(&x);
        sem_destroy(&y);
    }

    return 0;
}
