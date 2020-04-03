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
