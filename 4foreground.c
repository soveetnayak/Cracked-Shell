#include "headers.h"

void function_foreground(char *store[])
{
    pid_t pid;

    pid = fork();
    if (pid <0 )
    {
        printf("Error in fork\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // child
        int i;
        i = execvp(store[0], store);
        if (i == -1)
        {
            printf("Error: Execution failed\n");
            return;
        }
    }
    else
    {
        // parent
        cur_process.pid = pid;
        strcpy(cur_process.name, store[0]);
        waitpid(pid, NULL, WUNTRACED);

    }
}