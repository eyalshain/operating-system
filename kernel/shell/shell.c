#include "shell.h"
#include "../../libc/include/string.h"
#include "../../drivers/include/screen.h"

const char *prompt = "(EyalOS@)->$ ";

void execute_command(char *command)
{
    if (strcmp(command, "help") == 0)
    {
        print("\nAvailable commands:\n");
        print("help: show this message\n");
        print("clear: clear the screen\n");
        print("echo <text>: print text");
    }

    else if (strcmp(command, "clear") == 0)
    {
        clear_screen();
    }

    else if (strcmp(command, "echo"))
    
    {

    }

}