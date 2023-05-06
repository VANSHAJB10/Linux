// Write a program in C that creates a file called "output.txt", writes the text "Hello, World!" to it, and then closes the file.
#include <stdio.h>

int main() {
    // Open the file for writing
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return 1;
    }

    // Write the text to the file
    fprintf(file, "Hello, World!\n");

    // Close the file
    fclose(file);

    return 0;
}
