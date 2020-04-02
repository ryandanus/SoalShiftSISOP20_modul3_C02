#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define M 4
#define K 2
#define N 5
#define NUM_THREADS M * N

/* Global variables for threads to share */
// matriks 4x2
int A[M][K] = {{1, 4}, {2, 5}, {3, 6}, {1, 1}};
// matriks 2x5
int B[K][N] = {{8, 7, 6, 3, 1}, {5, 4, 3, 3, 1}};
int C[M][N];

/* Structure for passing data to threads */
struct v
{
    int i; /* row */
    int j; /* column */
};

void *runner(void *ptr); /* the thread */

int main(int argc, char **argv)
{
    int i, j ,iv = 0;
    int thread_counter = 0;
    key_t key = 1234;
    int *value;

    int SizeMem = sizeof(*value);
    
    int shmid = shmget(key, 20, IPC_CREAT | 0666);
    
    // value = shmat(shmid, NULL, 0);
    value = (int *)shmat(shmid, 0, 0);

    pthread_t workers[NUM_THREADS];
    
    /* create M * N worker threads */
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++) 
        {
            struct v *data = (struct v *) malloc(sizeof(struct v));
            data->i = i;
            data->j = j;
            /* create the thread passing it data as a paramater*/
            pthread_create(&workers[thread_counter], NULL, runner, data);
            pthread_join(workers[thread_counter], NULL);
            thread_counter++;
        }
    }
    
    /* Waiting for threads to complete */
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(workers[i], NULL);
   
    }
    
    for(i = 0; i < M; i++)
    { 
        for(j = 0; j < N; j++)
        { 
            // *value = C[i][j];
            printf("%d\t",C[i][j]);
             value[iv] = C[i][j];
             iv++;
        }

        printf("\n");
    }

    shmdt((void *) value);
    // shmdt(value);
    // shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

void *runner(void *ptr)
{    
    /* Casting paramater to struct v pointer */
    struct v *data = ptr;
    int i, sum = 0;
    
    for(i = 0; i < K; i++)
    {    
        sum += A[data->i][i] * B[i][data->j];
    }
    
    C[data->i][data->j] = sum;
    pthread_exit(0);
}

