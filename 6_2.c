/*
Write a program using pthread to find the length of string, where strings are passed to thread function.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_STRING_LENGTH 100

void *string_length(void *arg) {
    char *str = (char *) arg;
    int len = strlen(str);
    printf("Length of '%s' is %d\n", str, len);
    pthread_exit(NULL);
}

int main() {
    char str1[MAX_STRING_LENGTH], str2[MAX_STRING_LENGTH];
    pthread_t tid1, tid2;

    printf("Enter string 1: ");
    scanf("%s", str1);

    printf("Enter string 2: ");
    scanf("%s", str2);

    pthread_create(&tid1, NULL, string_length, (void *) str1);
    pthread_create(&tid2, NULL, string_length, (void *) str2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
