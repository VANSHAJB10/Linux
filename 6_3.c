/* Write a program that performs statistical operations of calculating the average, maximum and minimum for a set of numbers. 
Create three threads where each performs their respective operations. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

int nums[] = {4, 7, 2, 9, 1, 5, 8, 3, 6}; // Set of numbers
int num_count = sizeof(nums) / sizeof(int); // Number of elements in the set

double avg;
int max;
int min;

// Thread function to calculate average
void *calc_avg(void *arg) {
    int sum = 0;
    for (int i = 0; i < num_count; i++) {
        sum += nums[i];
    }
    avg = (double) sum / num_count;
    pthread_exit(NULL);
}

// Thread function to calculate maximum
void *calc_max(void *arg) {
    max = nums[0];
    for (int i = 1; i < num_count; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    pthread_exit(NULL);
}

// Thread function to calculate minimum
void *calc_min(void *arg) {
    min = nums[0];
    for (int i = 1; i < num_count; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create threads to calculate average, maximum, and minimum
    pthread_create(&threads[0], NULL, calc_avg, NULL);
    pthread_create(&threads[1], NULL, calc_max, NULL);
    pthread_create(&threads[2], NULL, calc_min, NULL);

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the results
    printf("Average: %.2f\n", avg);
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);

    return 0;

}
