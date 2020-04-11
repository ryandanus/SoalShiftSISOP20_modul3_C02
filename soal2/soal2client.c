#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <termios.h>
#include <stdbool.h>
#define PORT 8080


int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error\n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed\n");
        return -1;
    }
    char cmd[1024], cmd2[1024], username[1024], pass[1024], temp[1024], mode[1024];

    screenlogin:
    printf("1. Login\n2. Register\nChoices : ");
    scanf("%s", cmd);
    if (strcmp(cmd, "login") == 0)
    {
        strcpy(mode, "login");
        send(sock, mode, sizeof(mode), 0);
        printf("Username : ");
        getchar();
        scanf("%[^\n]", username);
        send(sock, username, strlen(username), 0);
        strcat(username, temp);
        printf("Password : ");
        getchar();
        scanf("%[^\n]", pass);
        printf("%s",pass);
        send(sock, pass, strlen(pass), 0);
        int feedback;
        read(sock, &feedback, sizeof(feedback));
        if (feedback)
        {
            printf("login success\n");
        screenCommand:
            // printf("1. Find Match\n2. Logout\nChoices : ");
            // getchar();
            // scanf("%[\n]", cmd2);
            // printf("%s",cmd2);
            // if (strcmp(cmd2, "logout") == 0)
            // {
            //     send(sock, cmd2, strlen(cmd2), 0);
                goto screenlogin;
            // }
            // else if (strcmp(cmd2, "find") == 0)
            // {
            //     send(sock, cmd2, strlen(cmd2), 0);
            //     goto screenCommand;
            // }
            // else
            // {
            //     printf("invalid input\n");
                // goto screenCommand;
            // }
        }
        else
        {
            printf("login failed\n");
            goto screenlogin;
        }
    }
    else if (strcmp(cmd, "register") == 0)
    {
        strcpy(mode, "register");
        send(sock, mode, sizeof(mode), 0);
        printf("Username : ");
        getchar();
        scanf("%[^\n]", username);
        send(sock, username, strlen(username), 0);
        printf("Password : ");
        getchar();
        scanf("%[^\n]", pass);
        printf("%s", pass);
        send(sock, pass, strlen(pass), 0);
        printf("register success\n");
        goto screenlogin;
    }
    else
    {
        printf("invalid input\n");
        goto screenlogin;
    }
    return 0;
}
