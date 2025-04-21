#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h>

#define MAX_READERS 5


int data = 0;
int totalReaders = 0;


void* reader(void* arg) { int id = *((int*)arg);

totalReaders++;
printf("Reader %d is reading data: %d\n", id, data); sleep(1);
totalReaders--;


return NULL;
}


void* writer(void* arg) { int id = *((int*)arg);

data++;
printf("Writer %d modified data to: %d\n", id, data);
 
sleep(1);


return NULL;
}


int main() {
pthread_t readers[MAX_READERS], writers[2]; int readerIds[MAX_READERS], writerIds[2];

for (int i = 0; i < MAX_READERS; i++) { readerIds[i] = i + 1;
pthread_create(&readers[i], NULL, reader, &readerIds[i]);
}


for (int i = 0; i < 2; i++) { writerIds[i] = i + 1;
pthread_create(&writers[i], NULL, writer, &writerIds[i]);
}


for (int i = 0; i < MAX_READERS; i++) { pthread_join(readers[i], NULL);
}
for (int i = 0; i < 2; i++) { pthread_join(writers[i], NULL);
}


return 0;
}
