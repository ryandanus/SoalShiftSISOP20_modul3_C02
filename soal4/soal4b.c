#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>s

#define M 4
#define K 2
#define N 5
#define NUM_THREADS M * N
int matriks;

void *penjumlahan(int *ptr); /* the thread */
int jumlah(int *n);



void main()
{
    int *value,fact;
    int i,j,iv;
    int thread_counter = 0;
    key_t key = 1234;
    
    int shmid = shmget(key, 20, IPC_CREAT | 0666);
    value = (int *)shmat(shmid, 0, 0);

    pthread_t workers[NUM_THREADS];
    pthread_attr_t attr; // set of thread attributes

    /* create  worker threads */
    for (i = 0; i < M*N; i++)
    {
        matriks = value[i];
        pthread_attr_init(&attr);
        pthread_create(&workers[thread_counter], &attr, penjumlahan, (void *)matriks);
        thread_counter++;
   
        if( (i%5) == 0){
            printf("\n");
        }
       
    }
  
        
    for (i = 0; i < thread_counter; i++)
    {
        pthread_join(workers[i], NULL);
   
    }
    
    shmdt((void *) value);
    // shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
}

int jumlah(int *n){
    int i,sum=0;
    for (i=n;i>=0;i--){
        sum=sum+i;
    }
    return sum;
}


void *penjumlahan(int *ptr)
{       
    printf("%d\t",jumlah(ptr));
    pthread_exit(0);
}
