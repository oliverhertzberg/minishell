#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

// Structure to store terminal settings
typedef struct {
    struct termios termio1;
    struct termios termio2;
} t_data;
