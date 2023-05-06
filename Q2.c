
//Write a program in C that reads the contents of a file called "input.txt" and writes them to a new file called "output.txt". You should use system calls like open(), read(), and write().
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    // Open the input file for reading
    int input_fd = open("input.txt", O_RDONLY);
    if (input_fd < 0) {
        printf("Error: Failed to open input file.\n");
        return 1;
    }

    // Open the output file for writing
    int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        printf("Error: Failed to open output file.\n");
        close(input_fd);
        return 1;
    }

    // Read from the input file and write to the output file
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytes_written = write(output_fd, buffer, bytes_read);
        if (bytes_written < 0) {
            printf("Error: Failed to write to output file.\n");
            close(input_fd);
            close(output_fd);
            return 1;
        }
    }

    // Check for errors during the read operation
    if (bytes_read < 0) {
        printf("Error: Failed to read from input file.\n");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    // Close the input and output files
    close(input_fd);
    close(output_fd);

    return 0;
}

