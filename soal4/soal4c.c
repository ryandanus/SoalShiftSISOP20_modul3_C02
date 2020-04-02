
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
