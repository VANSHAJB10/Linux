/* QUESTION -- 1

Write a program using pthread to concatenate the strings, where multiple strings are
passed to thread function.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_STRINGS 5
#define MAX_STRING_LENGTH 100

// Define a structure to hold the input data for the thread
typedef struct {
    char **strings;
    int num_strings;
    char *result;
} ThreadData;

// Thread function that concatenates all of the strings
void *concatenate_strings(void *arg) {
    ThreadData *data = (ThreadData *) arg;
    int i;

    // Concatenate all of the strings
    strcpy(data->result, "");
    for (i = 0; i < data->num_strings; i++) {
        strcat(data->result, data->strings[i]);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    ThreadData data;
    char **strings;
    char *result;
    int i;

    // Allocate memory for the input data
    strings = (char **) malloc(MAX_STRINGS * sizeof(char *));
    for (i = 0; i < MAX_STRINGS; i++) {
        strings[i] = (char *) malloc(MAX_STRING_LENGTH * sizeof(char));
    }
    result = (char *) malloc(MAX_STRINGS * MAX_STRING_LENGTH * sizeof(char));

    // Get the strings from the user
    printf("Enter %d strings to concatenate:\n", MAX_STRINGS);
    for (i = 0; i < MAX_STRINGS; i++) {
        printf("String %d: ", i + 1);
        fgets(strings[i], MAX_STRING_LENGTH, stdin);
        strings[i][strcspn(strings[i], "\n")] = 0; // Remove the newline character
    }

    // Set up the input data for the thread
    data.strings = strings;
    data.num_strings = MAX_STRINGS;
    data.result = result;

    // Create the thread
    pthread_create(&thread, NULL, concatenate_strings, &data);

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    // Print the concatenated string
    printf("Result: %s\n", result);

    // Free the memory
    for (i = 0; i < MAX_STRINGS; i++) {
        free(strings[i]);
    }
    free(strings);
    free(result);

    return 0;
}
