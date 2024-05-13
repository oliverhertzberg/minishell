#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

// Structure to store terminal settings
typedef struct {
    struct termios old_tio;
} t_data;

// Function prototype
void ctrl_d_cmd(char *line, t_data *ms);

int main() {
    t_data ms;

    // Store current terminal settings
    tcgetattr(STDIN_FILENO, &(ms.old_tio));

    char *input;

    printf("Enter input (Ctrl+D to exit):\n");
    while ((input = readline("> ")) != NULL) {
        // Call ctrl_d_cmd function to handle Ctrl+D
        ctrl_d_cmd(input, &ms);

        // Print input
        printf("You entered: %s\n", input);
        free(input);
    }

    // Exiting the loop means Ctrl+D was detected
    printf("Ctrl+D (EOF) detected. Program exiting.\n");

    return 0;
}

void ctrl_d_cmd(char *line, t_data *ms)
{
    if (line == NULL && feof(stdin))
    {
        // If input line is NULL (indicating EOF)
        // and feof indicates EOF from stdin
        // Restore terminal settings to their original state
        tcsetattr(STDIN_FILENO, TCSANOW, &(ms->old_tio));

        // Print "exit" message to indicate program exit
        printf("exit\n");

        // Exit the program with success status
        exit(0);
    }
}

