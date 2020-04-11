# SoalShiftSISOP20_modul3_C02

### Kelompok 
- Feinard             05111840000081
- Ryan Danu Saputra   05111840000144

SOAL 
  - [Nomor 2](#nomor-2)
  - [Nomor 3](#nomor-3)
  - [Nomor 4](#nomor-4)

JAWABAN
  - [2](#jawaban-2)
  - [3](#jawaban-3)
  - [4a](#jawaban-4a)
  - [4b](#jawaban-4b)
  - [4c](#jawaban-4c)

## Nomor 2
### Soal 2 :
Qiqi adalah sahabat MamMam dan Kaka. Qiqi , Kaka dan MamMam sangat senang
bermain “Rainbow six” bersama-sama , akan tetapi MamMam sangat Toxic ia selalu
melakukan Team killing kepada Qiqi di setiap permainannya. Karena Qiqi orang yang
baik hati, meskipun marah Qiqi selalu berkata “Aku nggk marah!!”. Kaka ingin
meredam kemarahan Qiqi dengan membuatkannya sebuah game yaitu TapTap
Game. akan tetapi Kaka tidak bisa membuatnya sendiri, ia butuh bantuan mu. Ayo!!
Bantu Kaka menenangkan Qiqi.
TapTap Game adalah game online berbasis text console. Terdapat 2 program yaitu
tapserver.c dan tapplayer.c
Syarat :
- Menggunakan Socket, dan Thread
Hint :
- fwrite, fread
Spesifikasi Game :

CLIENT SIDE

Screen 1 :
1. Login
2. Register
Choices : {your input}
★ Pada screen 1 kalian dapat menginputkan “login”, setelah menekan enter
anda diminta untuk menginputkan username dan password seperti berikut
Screen 1 :
1. Login
2. Register
Choices : login
Username : { ex : qiqi }
Password : { ex : aku nggak marah!! }
★ Jika login berhasil maka akan menampilkan pesan “login success”, jika gagal
akan menampilkan pesan “login failed” (pengecekan login hanya mengecek
username dan password, maka dapat multi autentikasi dengan username dan
password yang sama)
★ Pada screen 1 kalian juga dapat menginputkan “register”, setelah menekan
enter anda diminta untuk menginputkan username dan password sama
halnya seperti login
★ Pada register tidak ada pengecekan unique username, maka setelah register
akan langsung menampilkan pesan “register success” dan dapat terjadi
double account
★ Setelah login berhasil maka anda berpindah ke screen 2 dimana
menampilkan 2 fitur seperti berikut.

Screen 2 :
1. Find Match
2. Logout
Choices : {your input}
★ Pada screen 2 anda dapat menginputkan “logout” setelah logout anda akan
kembali ke screen 1
★ Pada screen 2 anda dapat menginputkan “find”, setelah itu akan
menampilkan pesan “Waiting for player ...” print terus sampai menemukan
lawan
★ Jika menemukan lawan maka akan menampilkan pesan “Game dimulai
silahkan tap tap secepat mungkin !!”
★ Pada saat game dimulai diberikan variable health = 100,dan anda dapat
men-tap (menekan space pada keyboard tanpa harus menekan enter)
★ Pada saat anda men-tap maka akan menampilkan pesan “hit !!”, dan pada
lawan healthnya akan berkurang sebanyak 10 kemudian pada lawan
menampilkan pesan status healthnya sekarang. (conclusion : anda tidak bisa
melihat status health lawan)
★ Jika health anda <= 0 maka akan menampilkan pesan “Game berakhir kamu
kalah”, apabila lawan anda healthnya <= 0 maka akan menampilkan pesan
”Game berakhir kamu menang”
★ Setelah menang atau kalah maka akan kembali ke screen 2

SERVER SIDE

★ Pada saat program pertama kali dijalankan maka program akan membuat file
akun.txt jika file tersebut tidak ada. File tersebut digunakan untuk menyimpan
username dan password
★ Pada saat user berhasil login maka akan menampilkan pesan “Auth success” jika
gagal “Auth Failed”
★ Pada saat user sukses meregister maka akan menampilkan List account yang
terdaftar (username dan password harus terlihat)

### Jawaban 2
Client
```c
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
```
server
```c
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
```
### penjelasan
  Untuk client side digunakan pendeklarasian client seperti biasa, kemudian dilakukan pembacaan pilihan register dan login. Jika register maka harus kembali ke screen1. Oleh karena itu digunakan goto sebagai penunjuk pengembalian. Jika sedang login maka dikirim perinah login ke server. Kemudian dimasukan username dan password dan dikirim ke server kembali dan menunggu perintah server apakah username dan password ada didalam server. Jika ada maka, ditunjukan dengan feedback dan dilanjutkan di program selanjutnya. Jika tidak maka dilakukan pengembalian ke menu login.
  
  Untuk register, dilakukan cara yang mirip dengan login. Tetapi perbedaannya hanya ketika setelah mengirimkan mode, username dan status dikembalikan ke screenlogin.Untuk server side pertama dilakukan deklarasi struct untuk akun yang akan digunakan dan struct untuk connection setiap client. Setelah itu, dilakukan deklarasi server biasa dengan menggunakan thread. Fungsi thread ini adalah sebagai pemegang setiap client yang ada. Untuk penanda thread client dapat digunakan sistem accept pada client[i]. Jika terdapat client maka dimasukan kedalam struct client_serv dan dibuat thread.
  Sistem akan menunggu sampai dicapai client maksimum. Setelah itu, didalam thread itu sendiri, pertama dideklarasi log dan cid sebagai penanda login dan register. Didalam server digunakan screen1 sebagai login dan screen2 sebagai logout dan find match. Didalam program ini belum diimplementasi screen2. Didalam login ini pertama diambil jenis perintah dari client untuk login dan register. kemudian diambil username dan passwordnya. Jika login, maka dilakukan pembacaan akun.txt dengan fopen. kemudian semua username dan password tersebut dimasukan kedalam struct akun dan dimasukan kedalam list account. Kemudian dilakukan pengeccekan apabila username dan password tersebut ada didalam list account. Jika ada maka dikirim perintah login success, Jika tidak maka dikirim perintah login failed. Untuk register ini, hanya melakukan fprintf kedalam akun.txt dan dikembalikan ke screen1 

## Nomor 3
### Soal 3 :
Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan
memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah
sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working
directory ketika program kategori tersebut dijalankan.
● Semisal program dijalankan:
# File kategori terletak di /home/izone/kategori
$ ./kategori -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
|-jpg
|--file1.jpg
|-c
|--file2.c
|-zip
|--file3.zi
● Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa
dikategorikan sebanyak yang user inginkan seperti contoh di atas.
● Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual,
melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,
maka dia akan disimpan dalam folder “Unknown”.
● Program kategori ini juga menerima perintah (*) seperti di bawah;
$ ./kategori \*
● Artinya mengkategori seluruh file yang ada di working directory ketika
menjalankan program C tersebut.
● Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori
pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory
saja, tidak seperti file yang bebas menginput file sebanyak mungkin.
$ ./kategori -d /path/to/directory/
● Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan
hasilnya akan disimpan di working directory di mana program C tersebut
berjalan (hasil kategori filenya bukan di /path/to/directory).
● Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau
menggunakan (*) terdapat folder yang berisi file, maka file dalam folder
tersebut tidak dihiraukan, cukup file pada 1 level saja.
● Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan
secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang
juga menggunakan fork-exec dan system.
● Silahkan download soal3.zip sebagai percobaan. Namun silahkan
dicoba-coba sendiri untuk kemungkinan test case lainnya yang mungkin
belum ada di soal3.zip.

### Jawaban 3
```c
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
Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri
jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap
pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan
setiap batunya memiliki warna yang berbeda.
Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat
mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di
pilar tersebut. Norland menghampiri setiap pilar secara bergantian.
- Batu mulia pertama. Emerald. Batu mulia yang berwarna hijau mengkilat. Pada
batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:
1. Buatlah program C dengan nama "4a.c", yang berisi program untuk
melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan
matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks
nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
2. Tampilkan matriks hasil perkalian tadi ke layar.

- Batu kedua adalah Amethyst. Batu mulia berwarna ungu mengkilat. Teka-tekinya
adalah:

1. Buatlah program C kedua dengan nama "4b.c". Program ini akan
mengambil variabel hasil perkalian matriks dari program "4a.c" (program
sebelumnya), dan tampilkan hasil matriks tersebut ke layar.
(Catatan!: gunakan shared memory)
2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks
tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan
format seperti matriks.

Contoh: misal array [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], ...],

maka:

1 2 6 24
120 720 ... ...
...

(Catatan! : Harus menggunakan Thread dalam penghitungan
faktorial)
- Batu ketiga adalah Onyx. Batu mulia berwarna hitam mengkilat. Pecahkan
teka-teki berikut!

1. Buatlah program C ketiga dengan nama "4c.c". Program ini tidak
memiliki hubungan terhadap program yang lalu.
2. Pada program ini, Norland diminta mengetahui jumlah file dan
folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar
IPC, Norland mengerjakannya dengan semangat.
(Catatan! : Harus menggunakan IPC Pipes)
Begitu batu terakhir berhasil didapatkan. Gemuruh yang semakin lama semakin
besar terdengar. Seluruh tempat berguncang dahsyat, tanah mulai merekah. Sebuah
batu yang di atasnya terdapat kotak kayu muncul ke atas dengan sendirinya.

Sementara batu tadi kembali ke posisinya. Tanah kembali menutup, seolah tidak
pernah ada lubang merekah di atasnya satu detik lalu.
Norland segera memasukkan tiga buah batu mulia Emerald, Amethys, Onyx pada
Peti Kayu. Maka terbukalah Peti Kayu tersebut. Di dalamnya terdapat sebuah harta
karun rahasia. Sampai saat ini banyak orang memburu harta karun tersebut.
Sebelum menghilang, dia menyisakan semua petunjuk tentang harta karun tersebut
melalui tulisan dalam buku catatannya yang tersebar di penjuru dunia. "One Piece
does exist".


### Jawaban 4a
```c

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
  Sesuai dengan petunjuk soal untuk digunakannya shared memory pada soal 4a dan 4b. Shared memory sendiri didalam program ini cukup unik. Dalam program digunakan dua shared memmory. Pertama untuk sharing value dari matrix hasil 4.a. Dan kedua, untuk sharing value mutex. Mutex didalam ini atau disebut status digunakan untuk penandaan program 4b telah berjalan. thread yang berjalan berjumlah sesuai dengan indeks matrix yaitu 20 thread yang akan menjalankan perkalian matrix setelah semua thread matrix itu selesai bekerja dilakukan looping untuk print hasil perkalian matrix tersebut


### Jawaban 4b
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
  Untuk 4b ini, digunakan shared memory yang ada dari 4a.
thread yang berjalan se-jumlah  total matriks yang ada. Pertama shared memory value dideklarasi  dan shmget,shmat untuk status. Kemudian deklarasi matrix dan hasilAkhir dari faktorisasi matriks didalam global variable.

Tidak hanya itu dideklarasi x dan y sebagai iterasi matrix dan sebagai penanda x dan y matrix yang dimaksud sebagai hasil akhir. Tujuan digunakan global variable adalah agar multithread dapat membaca matrix dengan mudah tanpa harus dilakukan passing parameter. Dengan looping digunakan penetapan status shared memori menjadi 1 yang menanda bahwa program 4b telah berjalan. Kemudian dilakukan pembacaan value dan dimasukan kedalam matriks yang telah dibuat. Setelah pembacaan value shared memory selesai kemudian dilakukan pembuatan thread setiap isi matriks yang ada, sejumlah 20 kali.

Setiap pembacaan isi baris dari awal sampai selesai akan dilakukan pembacaan baris selanjutnya. Didalam thread sendiri ini akan digunakan rekursi penambahan dari nilai matrix x dan y kedalam hasil Akhir x dan y. Didalam recursive ini akan dilakukan penambahan dari n+n-1 yang dipassing sampai 1 ataupun 0. Kemudian setelah semua thread selesai bekerja, dilakukan looping x dan y untuk melakukan print dari matrix hasilakhir berupa hasil penjumlahan sesuai dengan deskripsi soal

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
  pada 4.c ,program ini dijalankan menggunakan sebuah pipe melalui fork(); dan akan menampilkan suatu jumlah file folder

syntax dup2(link[1], STDOUT_FILENO); digunakan untuk menghasilkan output dari apa yang akan dijalankan ke link1. Setelah itu ditutup dengan perintah " close "

perintah eksekusi ls akan dijalankan melalui fork yang diletakkan di child sedangkan wc -l diletakkan di parent
hasil output dari program ini akan  sesuai dengan seperti saat perintah ls | wc -l dijalankan 
    
# Kendala
