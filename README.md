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
```
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <limits.h>

#define maxthread 1000
#define MAX 10000
int a = 1;
char backupPath[10000];

void* checkfile()
{
    printf("CHECK DATA START\n");
    char dataPath[10000];
    strcpy(dataPath,backupPath);

    struct stat typestat;

    if (stat(dataPath, &typestat) != -1)
    {
        if (S_ISDIR(typestat.st_mode) != 0)
        {
            printf("IS DIRECTORY\nFinished\n");
            a=1;
            return 0;
        }
        else if (S_ISREG(typestat.st_mode) != 0)
        {
            printf("Check type of file\n");
            struct stat st;
            char movinglocation[10000], extensi[1000];

            getcwd(movinglocation,1000);
            strcat(movinglocation, "/");

            char *pch;
            pch = strrchr(dataPath, '.');



            if(pch == NULL )
            {
                printf("A no extention file\n");
                FILE *fp1, *fp2;
                strcat(movinglocation, "unknown");

                mkdir(movinglocation,0777);
                strcat(movinglocation, "/");

                int indexremove = 0;
                pch = strrchr(dataPath, '/');

                char temp[1000];
                strcpy(temp, pch);
                memmove(&temp[indexremove], &temp[indexremove + 1], strlen(temp) - indexremove);

                strcat(movinglocation, temp);

                int ch;

                printf("Moving location = %s\n",movinglocation);

                fp1 = fopen(dataPath, "rb");
                fp2 = fopen(movinglocation, "wb");

                if (!fp1)
                {
                    printf("Unable to open source file to read!!\n");
                    fclose(fp2);
                    return 0;
                }

                if (!fp2)
                {
                    printf("Unable to open target file to write\n");
                    fclose(fp2);
                    return 0;
                }
                while ((ch = fgetc(fp1)) != EOF)
                {
                    fputc(ch, fp2);
                }

                fclose(fp1);
                fclose(fp2);
                printf("FINISHED\n");
                a = 1;

                return 0;
            }
          

            else
            {
                int indexremove = 0;

                strcpy(extensi, pch);
                memmove(&extensi[indexremove], &extensi[indexremove + 1], strlen(extensi) - indexremove);

                //check extensi type;
                for (int i = 0; i < strlen(extensi); i++)
                {
                    if(extensi[i] >= 'A' && extensi[i] <= 'Z')
                    {
                        extensi[i] = extensi[i]+32;
                    }
                }

                strcat(movinglocation, extensi);
                printf("Extensi name : %s\n",extensi);

                //check extensi bintang
                if(strcmp(extensi,"*") == 0){

                    printf("A no extention file\n");
                    getcwd(movinglocation,1000);
                    strcat(movinglocation, "/unknown/");

                    mkdir(movinglocation, 0777);

                    FILE *fp1, *fp2;

                    int indexremove = 0;
                    pch = strrchr(dataPath, '/');

                    char temp[1000];
                    strcpy(temp, pch);
                    memmove(&temp[indexremove], &temp[indexremove + 1], strlen(temp) - indexremove);

                    strcat(movinglocation, temp);

                    int ch;

                    printf("Moving location = %s\n", movinglocation);

                    fp1 = fopen(dataPath, "rb");
                    fp2 = fopen(movinglocation, "wb");
                    printf("%s %s",dataPath,movinglocation);

                    if (!fp1)
                    {
                        printf("Unable to open source file to read!!\n");
                        fclose(fp2);
                        return 0;
                    }

                    if (!fp2)
                    {
                        printf("Unable to open target file to write\n");
                        fclose(fp2);
                        return 0;
                    }
                    while ((ch = fgetc(fp1)) != EOF)
                    {
                        fputc(ch, fp2);
                    }

                    fclose(fp1);
                    fclose(fp2);
                    printf("\nFINISHED\n");
                    a = 1;

                    return 0;
                }

                DIR *dir = opendir(movinglocation);
                if (dir)
                {
                    closedir(dir);
                    printf("moving directory\n");
                    int ch;

                    FILE *fp1, *fp2;


                    char namafile[1000];
                    pch = strrchr(dataPath, '/');
                    strcpy(namafile, pch);
                    memmove(&namafile[indexremove], &namafile[indexremove + 1], strlen(namafile) - indexremove);
                    strcat(movinglocation,"/");
                    strcat(movinglocation, namafile);

                    printf("Moving location = %s ", movinglocation);

                    fp1 = fopen(dataPath, "rb");
                    fp2 = fopen(movinglocation, "wb");

                    if (!fp1)
                    {
                        printf("Unable to open source file to read!!\n");
                        fclose(fp2);
                        return 0;
                    }

                    if (!fp2)
                    {
                        printf("Unable to open target file to write\n");
                        fclose(fp2);
                        return 0;
                    }
                    while ((ch = fgetc(fp1)) != EOF)
                    {
                        fputc(ch, fp2);
                    }

                    fclose(fp1);
                    fclose(fp2);
                    printf("\nFINISHED\n");
                    a = 1;

                    return 0;
                }
                else if (ENOENT == errno)
                {
                    printf("Make New Directory\n");
                    mkdir(movinglocation, 0777);
                    int ch;
                    FILE *fp1, *fp2;

                    char namafile[1000];
                    pch = strrchr(dataPath, '/');
                    strcpy(namafile, pch);
                    memmove(&namafile[indexremove], &namafile[indexremove + 1], strlen(namafile) - indexremove);
                    strcat(movinglocation,"/");
                    strcat(movinglocation,namafile);

                    printf("Movinf Location %s\n",movinglocation);

                    fp1 = fopen(dataPath,"rb");
                    fp2 = fopen(movinglocation, "wb");

                    if (!fp1)
                    {
                        printf("Unable to open source file to read!!\n");
                        fclose(fp2);
                        return 0;
                    }

                    if (!fp2)
                    {
                        printf("Unable to open target file to write\n");
                        return 0;
                    }
                    while ((ch = fgetc(fp1)) != EOF)
                    {
                        fputc(ch, fp2);
                    }
                    fclose(fp1);
                    fclose(fp2);

                    printf("\nFINISHED\n");
                    a = 1;
                    return 0;
                }
            }
        }
        else{
            a = 1;
            printf("error path\n");
            return 0;
        }
    }
}


int main(int argc, char const *argv[])
{
    pthread_t threadfile[maxthread];

    if (strcmp(argv[1], "-f") == 0)
    {
        int loop = 0;
        for (int i = 1; i < argc - 1; i++)
        {
            strcpy(backupPath,argv[i+1]);
            pthread_create(&threadfile[loop], NULL, &checkfile,NULL);
            while (a == 0)
            {
            }
            a = 0;
            
            loop++;
        }
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        struct dirent *directoryDirent;
        DIR *file = opendir(argv[2]);
        if (file == NULL)
        {
            printf("ERROR READ");
        }
        int loop = 0;
        while ((directoryDirent = readdir(file)) != NULL)
        {

            char filepath[80];
            struct stat typestat;

            printf("Nama File = %s\n", directoryDirent->d_name);

            if (strcmp(directoryDirent->d_name, ".") == 0 || strcmp(directoryDirent->d_name, "..") == 0)
            {
                continue;
            }
            else
            {
                while (a == 0)
                {
                }
                a = 0;
                strcpy(filepath, argv[2]);
                strcat(filepath, "/");
                strcat(filepath,directoryDirent->d_name);

                strcpy(backupPath,filepath);

                printf("FILEPATH = %s\n", filepath);

                pthread_create(&(threadfile[loop]), NULL, checkfile,NULL);
                pthread_join(threadfile[loop], NULL);
                loop++;
            }
        }
    }
    else
    {
        if (strcmp(argv[1], "*") == 0)
        {
            char temp[1000];
            getcwd(temp,sizeof(temp));

            struct dirent *directoryDirent;
            DIR *file = opendir(temp);
            if(file == NULL){
                printf("ERROR READ");
            }
            int loop = 0;
            while ((directoryDirent = readdir(file)) != NULL)
            {
                char filepath[80];
                struct stat typestat;

                printf("Nama File = %s\n",directoryDirent->d_name);
                
                if (strcmp(directoryDirent->d_name, ".") == 0 || strcmp(directoryDirent->d_name, "..") == 0)
                {
                    continue;
                }
                else
                {
                    while (a == 0)
                    {
                    }
                    a = 0;

                    char temp[1000];
                    getcwd(temp, sizeof(temp));
                    strcpy(filepath, temp);

                    strcat(filepath,"/");
                    //check space;
                    int b = sizeof(directoryDirent->d_name)+2;
                    char temp2[b];
                    strcpy(temp2,directoryDirent->d_name);

                    int flag = 0;
                  
                    for (int i = 0; i < strlen(temp2); i++)
                    {
                        if(temp2[i] == 32)
                        {
                            flag++;
                        }
                    }

                    if(flag > 0){
                        char temp3[1000];
                        snprintf(temp2, 1024, "%s", directoryDirent->d_name);
                        printf("change name to : %s\n",temp2);
                    }
                    else
                    {
                        snprintf(temp2,1024,"%s",directoryDirent->d_name);
                    }
                    
                    strcat(filepath, temp2);
                    printf("FILEPATH = %s\n",filepath);
                    
                    strcpy(backupPath,filepath);

                    pthread_create(&(threadfile[loop]), NULL, checkfile,NULL);
                    pthread_join(threadfile[loop],NULL);
                    loop++;
                }
            }
        }
        else
        {
            a = 0;
            pthread_create(&(threadfile[0]), NULL, checkfile, (void *)argv[1]);
            while (a == 0)
            {
            }
            
            return 0;
        }
    }
    return 0;
}
```
### penjelasan 
Pertama dengan membaca jenis pembukaan, jika -f -d dan jika hanya path saja ataupun bintang. Jika -f maka dilakukan pembacaan setiap path kemudian membuat thread. Kemudian dengan mutek kita tunggu program selesai kemudian membaca path selanjutnya. Jika -d maka pertama membaca path. Kemudian penempatan path didalam directory itu dengan nama filepath. Kemudian membuat thread dan menjoin thread. Program akan membaca terus directory yang diberikan sampai habis.Kemudian untuk bintang, dilakukan pembacaan path program dengan getcwd. Kemudian dilakukan hal yang sama dengan  -d, pembacaan path yang ada di directory tersebut sampain habis. Dan jika hanya diinput path saja maka hanya dilakukan penetapan backuppath atau filepath yang ada dan dilakukan tread untuk pengecekan path. 

Untuk checkfile ini sendiri pertama memasukan datapath dari path yang sudah ada. Kemudian dilakukan pengecekan apabia path yang ingin dicek adalah folder ataupun file. Jika file maka dapat dilakukan pembacaan extensi dan pembacaan lokasi program.untuk pembacaan lokasi program dapat digunakan getcwd.  Untuk pembacaan extensi dapat digunakan strrchr dan titik yang bertujuan untuk membaca setelah . terakhir suatu file atau yang disebut extensi file. Jika tidak ditemukan extensi maka dapat dilakukan pembuatan file. Pertama kita ambil moving location yang diberi nama path program / unknown / nama file. Kemudian dilakukan mkdir folder unknown tersebut. Setelah itu dilakukan pemindahan dengan byte dengan fopen kedua path yang ada. Dilakukan fgetc dari source path ke moving location yang diinginkan. Kemudian program menunjukan mutex selesai dan program berakhir.
Setelah dilakukan strrchr maka dilakukan pembuangan titik di awal array dengan memmove. Jika terdapat extensi yang melebihi batas integer dari A sampai z maka diprogram akan berjalan seperti program tidak memiliki extensi. Jika extensi memiliki huruf besar A-Z maka dilakukan pengubahan menjadi huruf kecil atau penambahan 32 dengan ascii code. Setelah itu dilakukan pengecekan jika folder extensi ada menggunakan opendir.Jika ada maka tinggal penyiapan movinglocation dengan nama extensi dan nama file dan dilakukan fopen ke moving location tersebut. Kemudian dibuka datapath yang ada dan dilakukan fgetc dari datapath ke movinglocation sampai selesain. Kemudian penandaan mutex dan program selesai. Jika tidak ada folder dengan nama extensi, maka dapat dilakukan pembuatan folder terlebih dahulu dengan movinglocation pathprogram/namaextensi dan dengan mkdir moving location. Kemudian program berjalan seperti biasa.

## Nomor 4
### Soal 4 :

### Jawaban 4a
``` 

    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <unistd.h>

    #define M 4
    #define N 5
    #define O 2
    #define NUM_THREADS M *N

    struct v
    {
      int i; /* row */
      int j; /* column */
    };

    int A[M][O] = {{1, 4}, {2, 5}, {3, 6}, {1, 1}};
    int B[O][N] = {{8, 7, 6, 3, 1}, {5, 4, 3, 3, 1}};
    int C[M][N];

    void *runner(void *ptr)
    {
      struct v *data = ptr;
      int i, sum = 0;

      for (i = 0; i < 2; i++)
      {
        sum += A[data->i][i] * B[i][data->j];
      }

      C[data->i][data->j] = sum;
      pthread_exit(0);
    }

    int main(int argc, char **argv)
    {
      key_t key = 1234;
      key_t key2 = 2345;
      int *value;

      int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
      value = shmat(shmid, NULL, 0);

      int *status;
      int shmid2 = shmget(key2,sizeof(int),IPC_CREAT | 0777);
      status = shmat(shmid2,NULL,0);
      *status = 0;

      pthread_t workers[NUM_THREADS];
      int thread_counter;

      for (int i = 0; i < M; i++)
      {
        for (int j = 0; j < N; j++)
        {
          struct v *data = (struct v *)malloc(sizeof(struct v));
          data->i = i;
          data->j = j;
          /* create the thread passing it data as a paramater*/
          pthread_create(&workers[thread_counter], NULL, runner, data);
          pthread_join(workers[thread_counter], NULL);
          thread_counter++;
        }
      }

      for (size_t i = 0; i < 4; i++)
      {
        for (size_t j = 0; j < 5; j++)
        {
          printf("%d ",C[i][j]);
        }
        printf("\n");
      }
      

      for (int i = 0; i < 4; i++)
      {
          for (int j = 0; j < 5; j++)
          {
            while (*status == 0)
            {
            }
            *value = C[i][j];
            sleep(1);
          }
          printf("\n");
      }

      shmdt(value);
      shmdt(status);
      shmctl(shmid, IPC_RMID, NULL);
      shmctl(shmid2, IPC_RMID, NULL);
      return 0;
    }

```
### penjelasan 


### Jawaban 4b
```
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
