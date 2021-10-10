#include "headers.h"

void check_process()
{
    pid_t p;
    int s;
    p = waitpid(-1, &s, WNOHANG);

    for (int i = 1; i < processes_count+1; i++)
    {
        if (p < 0)
        {
            perror("Waitpid failed\n");
        }
        const int exit = WEXITSTATUS(s);

        if (WIFEXITED(s))
        {
            if (p == processes[i].pid)
            {
                printf("%s with pid %d exited ", processes[i].name, p);
                if (exit == 0)
                {
                    printf("normally.");
                }
                else
                {
                    printf("abnormally.");
                }

                fflush(stdout);
            }
        }
    }
}