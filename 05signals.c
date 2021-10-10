#include "headers.h"

void ctrl_z()
{
    pid_t temp = getpid();
    if (temp != shellid)
    {
        if (cur_process.pid != -1)
        {
            //kill(cur_process.pid, SIGTTIN);
            printf("Hi");
            if(kill(temp, SIGTSTP)==-1)
            {
                printf("Error: kill\n");
            }
            processes_count += 1;
            job_count += 1;
            processes[processes_count].job_no = cur_process.job_no;
            processes[processes_count].pid = cur_process.pid;
            strcpy(processes[processes_count].name, cur_process.name);

            cur_process.pid = -1;
            return;
        }
    }
    else
    {
        return;
    }
            printf("\n");
}
void ctrl_c()
{
    //printf("Here");
    pid_t temp = getpid();
    if (temp == shellid)
    {
        if (cur_process.pid != -1)
        {
            kill(cur_process.pid, SIGINT);
            cur_process.pid = -1;
            fflush(stdout);
        }
    }
    else
        return;

    signal(SIGINT, ctrl_c);
}