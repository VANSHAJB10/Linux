/* QUESTION - 2 
Write a program using system calls for operation on processes to create a hierarchy 
of processes as given in figure 1. Also, simulate process p4 as orphan and P5 as zombie.  

                P1
              /    \
             /      \
           P 2      P 4
            |        |
            |        |
            |        |
            |        |
           P 3      P 5                                                                                                       */
         
   
   
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t p1, p2, p3, p4, p5;

    p1 = getpid();
    printf("P1 (pid=%d, parent=%d)\n", p1, getppid());

    p2 = fork();
    if (p2 == 0) {
        printf("P2 (pid=%d, parent=%d)\n", getpid(), getppid());
        p3 = fork();
        if (p3 == 0) {
            printf("P3 (pid=%d, parent=%d)\n", getpid(), getppid());
        }
    } else {
        p4 = fork();
        if (p4 == 0) {
            printf("P4 (pid=%d, parent=%d)\n", getpid(), getppid());
            sleep(5);
        }
    }

    p5 = fork();
    if (p5 == 0) {
        printf("P5 (pid=%d, parent=%d)\n", getpid(), getppid());
        exit(0);
    }

    // wait for child processes to finish
    waitpid(p2, NULL, 0);
    waitpid(p4, NULL, WNOHANG);

    return 0;
   
}
