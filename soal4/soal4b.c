#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define M 4
#define K 2
#define N 5
#define NUM_THREADS M *N
int matriks[4][5];

int hasilAkhir[4][5];
int x = 0;
int y = 0;

int mutex = 0;

void *penjumlahan(); /* the thread */
int jumlah(int n);

void main()
{
    int *value;
    int *status;

    key_t key = 1234;
    key_t key2 = 2345;

    int shmid = shmget(key,sizeof(int), IPC_CREAT | 0666);
    value = (int *)shmat(shmid, 0, 0);

    int shmid2 = shmget(key2,sizeof(int),IPC_CREAT | 0777);
    status = (int *)shmat(shmid2,NULL,0);

    pthread_t thread[NUM_THREADS];
    int thread_counter = 0;

    for (int i = 0; i < 4; i++)
    {
        for(int j = 0 ; j < 5 ;j++)
        {   
            *status = 1;
            if(i == 0&& j == 0){
                sleep(1);
            }
            matriks[i][j] = *value;
            sleep(1);
        }
    }

    for (int i = 0; i < 20; i++)
    {
        pthread_create(&(thread[i]),NULL,penjumlahan,NULL);
        pthread_join(thread[i],NULL);
        if(y == 5){
            x++;
            y = 0;
        }
        y++;
    }
    

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            printf("%d ",hasilAkhir[i][j]);
        }
        printf("\n");
        
    }
    

    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
}

int jumlah(int n)
{
    if(n == 0){
        return 0;
    }
    if(n == 1)
    {
        return 1;
    }
    else
        return n+jumlah(n-1);
}

void *penjumlahan()
{
    hasilAkhir[x][y] = jumlah(matriks[x][y]);
    mutex = 1;
    pthread_exit(0);
}

//code kedua dan fix

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <unistd.h>s

// #define M 4
// #define K 2
// #define N 5
// #define NUM_THREADS M * N
// int matriks;

// void *penjumlahan(int *ptr); /* the thread */
// int jumlah(int *n);



// void main()
// {
//     int *value,fact;
//     int i,j,iv;
//     int thread_counter = 0;
//     key_t key = 1234;
    
//     int shmid = shmget(key, 20, IPC_CREAT | 0666);
//     value = (int *)shmat(shmid, 0, 0);

//     pthread_t workers[NUM_THREADS];
//     pthread_attr_t attr; // set of thread attributes

//     /* create  worker threads */
//     for (i = 0; i < M*N; i++)
//     {
//         matriks = value[i];
//         pthread_attr_init(&attr);
//         pthread_create(&workers[thread_counter], &attr, penjumlahan, (void *)matriks);
//         thread_counter++;
   
//         if( (i%5) == 0){
//             printf("\n");
//         }
       
//     }
  
        
//     for (i = 0; i < thread_counter; i++)
//     {
//         pthread_join(workers[i], NULL);
   
//     }
    
//     shmdt((void *) value);
//     // shmdt(value);
//     shmctl(shmid, IPC_RMID, NULL);
// }

// int jumlah(int *n){
//     int i,sum=0;
//     for (i=n;i>=0;i--){
//         sum=sum+i;
//     }
//     return sum;
// }


// void *penjumlahan(int *ptr)
// {       
//     printf("%d\t",jumlah(ptr));
//     pthread_exit(0);
// }
