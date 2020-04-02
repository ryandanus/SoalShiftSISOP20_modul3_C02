# SoalShiftSISOP20_modul3_C02

### Kelompok 
- Feinard             05111840000081
- Ryan Danu Saputra   05111840000144

SOAL 
  - [Nomor 1](#nomor-1)
  - [Nomor 2](#nomor-2)
  - [Nomor 3](#nomor-3)
  - [Nomor 4](#nomor-4)

JAWABAN
  - [1](#jawaban-1)
  - [2](#jawaban-2)
  - [3](#jawaban-3)
  - [4a](#jawaban-4a)
  - [4b](#jawaban-4b)
  - [4c](#jawaban-4c)

## Nomor 1
### Soal 1 :

### Jawaban 1

### penjelasan 

## Nomor 2
### Soal 2 :

### Jawaban 2

### penjelasan 

## Nomor 3
### Soal 3 :

### Jawaban 3

### penjelasan 

## Nomor 4
### Soal 4 :

### Jawaban 4a
```c
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

```
### penjelasan 


### Jawaban 4b
```c
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

void *factorial(int ptr); /* the thread */
int fact(int n);

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
    
    // print matriks
    for (iv = 0; iv< M*N; iv++)
    {   
        printf("%d\t",value[iv]);    
        if( (iv%5) == 4)printf("\n");
    
    }
    
    /* create  worker threads */
    for (i = 0; i < M*N; i++)
    {
        matriks = value[i];
        pthread_attr_init(&attr);
        pthread_create(&workers[thread_counter], &attr, &factorial, (void *)matriks);
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

int fact(int n){
    if(n==0 || n==1)
    return 1;
    else 
    return n*fact(n-1);
}

void *factorial(int ptr)
{       
    printf("%d\t",fact(ptr));
    pthread_exit(0);
}
```
### penjelasan 


### Jawaban 4c
```c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);


int main() {
    pid_t child_id;
    int status;
    int link[2];

    if (pipe(link)==-1){
       die("pipe");
    }
    child_id = fork();
   

    if (child_id == 0) {
        // this is child
        close(link[0]);
        dup2(link[1], STDOUT_FILENO);
        
        close(link[1]);                                                                                                  
        char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
    } 
    else {
    // this is parent

        // while ((wait(&status)) > 0);
        
        dup2(link[0], STDIN_FILENO);
        close(link[0]);
        close(link[1]);
        char *argv[] = {"wc", "-l", NULL};
        execv("/usr/bin/wc", argv);
    }

}
```
### penjelasan 


    
# Kendala
buset siap banget gan
