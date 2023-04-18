/*
Write a multithreaded program where an array of integers is passed globally and is divided into two smaller lists and given as input to two threads. 
The thread will sort their half of the list and will pass the sorted list to a third thread which merges and sorts the list. 
The final sorted list is printed by the parent thread.*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int arr[SIZE] = {5, 9, 2, 4, 7, 8, 1, 6, 3, 0};
int first_half[SIZE/2], second_half[SIZE/2];

void *sort_thread(void *arg)
{
    int *arr = (int *)arg;
    int i, j, temp;
    for (i = 0; i < SIZE/2; i++) {
        for (j = i+1; j < SIZE/2; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    pthread_exit(NULL);
}

void *merge_thread(void *arg)
{
    int *arr = (int *)arg;
    int i, j, k, temp;
    for (i = 0; i < SIZE/2; i++) {
        first_half[i] = arr[i];
        second_half[i] = arr[i+SIZE/2];
    }
    i = j = k = 0;
    while (i < SIZE/2 && j < SIZE/2) {
        if (first_half[i] < second_half[j]) {
            arr[k++] = first_half[i++];
        } else {
            arr[k++] = second_half[j++];
        }
    }
    while (i < SIZE/2) {
        arr[k++] = first_half[i++];
    }
    while (j < SIZE/2) {
        arr[k++] = second_half[j++];
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t sort_thread1, sort_thread2, merge_thread1;
    int i;

    printf("Unsorted Array: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_create(&sort_thread1, NULL, sort_thread, (void *)first_half);
    pthread_create(&sort_thread2, NULL, sort_thread, (void *)second_half);
    pthread_join(sort_thread1, NULL);
    pthread_join(sort_thread2, NULL);

    pthread_create(&merge_thread1, NULL, merge_thread, (void *)arr);
    pthread_join(merge_thread1, NULL);

    printf("Sorted Array: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
