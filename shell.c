#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while (1)
    {
        printf("#cisfun$ "); // Display the prompt
        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE); // Read user input

        if (bytes_read == -1)
        {
            perror("read"); // Handle read error
            exit(EXIT_FAILURE);
        }

        // Check for "end of file" condition (Ctrl+D)
        if (bytes_read == 0)
        {
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        buffer[bytes_read - 1] = '\0';

        // Fork to create a child process
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork"); // Handle fork error
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Child process
            if (execve(buffer, (char *[]) {buffer, NULL}, NULL) == -1)
            {
                perror("execve"); // Handle command execution error
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Parent process
            waitpid(pid, NULL, 0); // Wait for the child process to finish
        }
    }

    return EXIT_SUCCESS;
}
