#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define MAXREADERS 5
int data=0;
int readerCount=0;

sem_t x,y; //only for synchro

void* reader_sync(void* args)
{
    int id= *((int*)args);
    sem_wait(&x);
    readerCount++;
    if(readerCount==1)
        sem_wait(&y);
    sem_post(&x);

    printf("Reader %d is reading data %d\n",id,data);
    sleep(1);

    sem_wait(&x);
    readerCount--;
    if(readerCount==0)
        sem_post(&y);
    sem_post(&x);
    printf("Reader %d is done reading data...\n",id);
    return NULL;
}

void* writer_sync(void* args)
{
    int id= *((int*)args);
    printf("Writer %d is trying to enter...\n",id);
    sem_wait(&y);
    data++;
    printf("Writer %d has modified data to %d..\n",id,data);
    sleep(1);
    printf("Write %d is leaving..\n",id);
    sem_post(&y);
    return NULL;
}

void* reader_nosync(void* args)
{
    int id= *((int*)args);
    readerCount++;

    printf("Reader %d is reading data %d\n",id,data);
    sleep(1);

   
    readerCount--;
   
    printf("Reader %d is done reading data...\n",id);
    return NULL;
}

void* write_nosync(void* args)
{
    int id= *((int*)args);
    printf("Writer %d is trying to enter...\n",id);
    
    data++;
    printf("Writer %d has modified data to %d..\n",id,data);
    sleep(1);
    printf("Write %d is leaving..\n",id);
    
    return NULL;  
}
void main()
{
    pthread_t readers[MAXREADERS],writers[2];
    int readerID[MAXREADERS],writerID[2];
    int ch;
    printf("1.Without Synchronization\t2.With Synchronization\tEnter choice :");
    scanf("%d",&ch);
    if(ch==2)
    {
        sem_init(&x,0,1);
        sem_init(&y,0,1);
    }

    //create reader threads
    for(int i=0;i<MAXREADERS;i++)
    {
        readerID[i]=i+1;
        if(ch==1)
        pthread_create(&readers[i],NULL,reader_nosync,&readerID[i]);
        else
        pthread_create(&readers[i],NULL,reader_sync,&readerID[i]);
    }

    //create writer threads
    for(int i=0;i<2;i++)
    {
        writerID[i]=i+1;
        if(ch==1)
                pthread_create(&writers[i],NULL,write_nosync,&writerID[i]);
        else
                pthread_create(&writers[i],NULL,writer_sync,&writerID[i]);
    }

    //join reader threads
    for(int i=0;i<MAXREADERS;i++)
    {
        pthread_join(readers[i],NULL);
    }
    //join writers threads
    for(int i=0;i<2;i++)
    {
        pthread_join(writers[i],NULL);
    }

    if(ch==2)
    {
        sem_close(&x);
        sem_close(&y);
    }
}