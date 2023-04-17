/* 

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
pid_t pid1, pid2, pid3, pid4, pid5, pid6, pid7;

pid1 = getpid();
printf("Parent process ID %d\n", pid1);

pid2 = fork();
printf("P2 %d\n", pid2);
if (pid2 == 0) {
  pid3 = fork();
  printf("P3 %d\n", pid3);
    if (pid3 == 0) {
      pid4 = fork();
      printf("P4 %d \n", pid4);
        if (pid4 == 0) {
          sleep(3);
          printf("P4 is orphan\n");
        }
      else {
          wait(NULL);
        }
    } 
    else  
    {
      wait(NULL);
    }
 }
 else
 {
    pid5 = fork();
    printf("P5 %d\n", pid5);
    if (pid5 == 0) {
      pid6 = fork();
      printf("P6 %d \n", pid6);
        if (pid6 == 0) {
          pid7 = fork();
          printf("P7 %d \n", pid7);
            if (pid7 == 0) {
              printf("P7 is zombie\n");
              exit(0);
            } 
            else {
            wait(NULL);
            }
        } 
        else {
          wait(NULL);
        }
    } 
    else {
      wait(NULL);
    }
  }
return 0;
}
