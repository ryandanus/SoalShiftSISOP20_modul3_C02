#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#define PORT 8080

typedef struct akun
{
    char un[1024];
    char ps[1024];
} akun;

typedef struct client_serv
{
    int cid;
    int login;
} client_serv;

akun list_akun[100];
bool akun_cek, file_cek, conn_cek;
int conn, akun_n;

int id = 0;

void *ready(void *arg)
{
    client_serv cl = *(client_serv *)arg;
    int cid = cl.cid;
    int log = cl.login;
    if (log)
    {
    screen1:;
        char data[1024], un[1024], ps[1024], kode[1024], tempun[1024], tempps[1024];
        memset(data, 0, sizeof(data));
        read(cid, data, sizeof(data));
        strcpy(kode, data);
        memset(data, 0, sizeof(data));
        read(cid, data, sizeof(data)); //kode username password
        strcpy(un, data);
        memset(data, 0, sizeof(data));
        read(cid, data, sizeof(data));
        strcpy(ps, data);
        printf("kode  = %s\n username = %s\n password = %s\n", kode, un, ps);
        if (strcmp(kode, "login") == 0)
        {

            FILE *fp;
            char ch;
            fp = fopen("akun.txt", "a+");
            if (fp == NULL)
            {
                exit(0);
            }
            while (fscanf(fp, "%[^\n]\n%[^\n]\n", tempun, tempps) != EOF)
            {
                akun akun_baru;
                strcpy(akun_baru.un, tempun);
                strcpy(akun_baru.ps, tempps);
                list_akun[id] = akun_baru;
                id++;
            }

            akun_n = id;
            fclose(fp);

            bool done = 0;
            while (akun_cek)
                ;

            printf("username = %s\n password = %s\n", un, ps);
            for (int i = 0; i < akun_n; i++)
            {
                printf("id %s\npass %s\n", list_akun[i].un, list_akun[i].ps);
                if ((strcmp(un, list_akun[i].un) == 0) && (strcmp(ps, list_akun[i].ps) == 0))
                {
                    done = 1;
                    break;
                }
            }
            send(cid, &done, sizeof(done), 0);
            if (done)
                printf("Auth success\n");
            else
            {
                printf("Auth Failed\n");
                goto screen1;
            }
        }
        else if (strcmp(kode, "register") == 0)
        {
            printf("register\n%s\n%s\n", un, ps);
            akun_cek = 1;
            while (file_cek)
            {
            }
            file_cek = 1;
            FILE *fptr = fopen("akun.txt", "a");
            fprintf(fptr, "%s\n%s\n", un, ps);
            fclose(fptr);
            file_cek = 0;
            akun_cek = 0;
            printf("done");
            goto screen1;
        }
        else
        {
            printf("error\n");
        }
    }
    goto screen1;
    // printf("logout mode only available\n");
    // log = 1;
    // char kode[1024];
    // read(cid, kode, strlen(kode));
    // printf("%s\n", kode);
    // if (strcmp(kode, "logout") == 0)
    // {
    //     printf("screen1");
    //     goto screen1;
    // }
    // else if (strcmp(kode, "find") == 0)
    // {
    //     printf("screen1");
    //     goto screen1;
    // }
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    int c = 0;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(0);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(0);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(0);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(0);
    }

    akun_n = id;
    akun_cek = 0;
    file_cek = 0;
    conn = 0;
    conn_cek = 0;

    pthread_t th[2];
    int client[2];
    for (int i = 0; i < 2; i++)
    {
        client[i] = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client[i] < 0)
        {
            perror("can't accept client\n");
            i--;
            continue;
        }
        printf("client accepted\n");
        client_serv client_baru;
        client_baru.cid = client[i];
        client_baru.login = 1;
        pthread_create(&th[i], NULL, ready, (void *)&client_baru);
    }
    return 0;
}
