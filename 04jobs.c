#include "headers.h"

void printjobs(char *store[], int count)
{
    if (processes_count < 1)
    {
        processes_count = 0;
        printf("No jobs\n");
    }
    else
    {
        process temp_arr[processes_count];
        for (int i = 0; i < processes_count; i++)
        {
            temp_arr[i] = processes[i + 1];
        }

        qsort(temp_arr, processes_count, sizeof(process), comparator);

        if (count == 1 || count == 3)
        {

            for (int i = 0; i < processes_count; i++)
            {
                char file[10000], status, s[100000];

                sprintf(file, "/proc/%d/stat", temp_arr[i].pid);

                FILE *fd;
                fd = fopen(file, "r");

                if (fd == NULL)
                    printf("Error: no such process exists\n");
                else
                {

                    fscanf(fd, "%*d %*s %c", &status);
                    fclose(fd);

                    if (status == 'T')
                        printf("[%d] Stopped %s [%d]\n", i, temp_arr[i].name, temp_arr[i].pid);
                    else if(status == 'R' || status == 'S')
                        printf("[%d] Running %s [%d]\n", i, temp_arr[i].name, temp_arr[i].pid);

                    fflush(stdout);
                }
            }
        }
        else if (count == 2)
        {
            if (store[1][1] != 's' && store[1][1] != 'r')
            {
                printf("Invalid argument\n");
                return;
            }
            for (int i = 0; i < processes_count; i++)
            {
                char file[10000], status, s[100000];

                sprintf(file, "/proc/%d/stat", temp_arr[i].pid);
                FILE *fd;
                fd = fopen(file, "r");
                if (fd < 0)
                    printf("Error: no such process exists\n");
                else
                {
                    fscanf(fd, "%*d %*s %c", &status);
                    fclose(fd);
                }

                if (status == 'T' && store[1][1] == 's')
                    printf("[%d] Stopped %s [%d]\n", i, temp_arr[i].name, temp_arr[i].pid);
                else if ((status == 'R' || status == 'S') && store[1][1] == 'r')
                    printf("[%d] Running %s [%d]\n", i, temp_arr[i].name, temp_arr[i].pid);
            }
        }
        else
        {

            printf("Too many arguments\n");
        }
    }
}
void sig(int job_no, int sig_no)
{
    for (int i = 1; i <= processes_count; i++)
    {
        if (processes[i].job_no == job_no)
        {
            int status;
            status = kill(processes[i].pid, sig_no);
            if (status == -1)
                perror("Error: No such process exists\n");
        }
    }
}
void fg(char *store[])
{
    int check = 0;
    int job_no = atoi(store[1]);
    for (int i = 1; i <= processes_count; i++)
    {
        if (processes[i].job_no == job_no)
        {
            int status;
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, processes[job_no].pid);

            cur_process.pid = processes[job_no].pid;
            strcpy(cur_process.name, processes[job_no].name);
            kill(processes[job_no].pid, SIGCONT);
            delete_process(processes[job_no].pid);
            waitpid(-1, NULL, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            check = 1;
        }
    }
    if (check == 0)
        printf("Error: No such process found\n");
}

void bg(char *store[])
{
    int job_no = atoi(store[1]);
    int flag = 0;
    if (processes_count < 1)
    {
        printf("Error: No such job found\n");
        processes_count = 0;
        return;
    }
    else
    {
        for (int i = 1; i <= processes_count; i++)
        {
            if (processes[i].job_no == job_no)
            {
                kill(processes[job_no].pid, SIGCONT);
                flag = 1;
            }
        }
    }
    if (flag == 0)
    {
        printf("Error: No such job found\n");
    }
}

void delete_process(int id)
{

    int flag = 0;
    if (processes_count < 1)
    {
        printf("Error: No such job found\n");
        processes_count = 0;
        return;
    }
    else
    {
        for (int i = 1; i <= processes_count; i++)
        {
            if (processes[i].pid == id)
            {
                for (int j = i; j <= processes_count; j++)
                {
                    processes[j] = processes[j + 1];
                }
                processes_count = processes_count - 1;
                flag = 1;
            }
        }
    }
    if (flag == 0)
    {
        printf("Error: No such job found\n");
    }
}