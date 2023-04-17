/* QUESTION --  2nd (1) 
Write a program using systems for operations on processes to create a hierarchy of
processes P1 → P2 → P3. Also print the id and parent id for each process.  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;

    // fork first child process
    pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Error: Failed to fork first child\n");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // first child process
        printf("P2: Process ID = %d, Parent ID = %d\n", getpid(), getppid());

        // fork second child process
        pid2 = fork();

        if (pid2 < 0) {
            fprintf(stderr, "Error: Failed to fork second child\n");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // second child process
            printf("P3: Process ID = %d, Parent ID = %d\n", getpid(), getppid());
        } else {
            // parent process of second child
            wait(NULL);
        }
    } else {
        // parent process of first child
        wait(NULL);
    }

    // P1 process
    printf("P1: Process ID = %d\n", getpid());

    return 0;
}
