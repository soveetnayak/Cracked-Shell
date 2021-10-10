#include "headers.h"

void main_pipe(char *args[], int count, char home[], char last_wd[])
{
    int i = 0;

    int fd[2];
    int fd2[2];

    int input = 0;
    int output = 0;
    char buffer[100000], arg[10000], temp[10000];
    while (i < count)
    {
        strcpy(arg, args[i]);
        int oldout, oldin, ofd, ifd;
        int r = 0;
        char *part[10000], *part2[10000];

        part[0] = strtok(arg, " \n");
        int j = 0;
        int check;
        while (part[j] != NULL)
        {
            j++;
            part[j] = strtok(NULL, " \n");
        }

        if (i % 2 == 0)
        {
            check = pipe(fd);
            if (check < 0)
                perror("Error: pipe could not be created\n");
        }
        else
        {
            check = pipe(fd2);
            if (check < 0)
                perror("Error: pipe could not be created\n");
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            printf("Error: Fork failed\n");
        }
        else if (pid == 0)
        {
            if (i == 0)
            {
                dup2(fd[1], 1); // output to pipe
                close(fd[0]);   //closing input end of pipe
                strcpy(temp, args[i]);
            }
            else if (i == count - 1)
            {
                if (i % 2 == 1)
                {
                    // printf("came into odd end\n");
                    dup2(fd[0], 0); //inputut from pipe
                }
                else
                {
                    // printf("came into even end\n");
                    dup2(fd2[0], 0); //inputut from transit
                }
            }
            else if (i % 2 == 0)
            {
                // printf("came into even middle\n");
                dup2(fd2[0], 0); //inputut from transit
                close(fd[0]);    // close inputut end of pipe
                dup2(fd[1], 1);  // outputut to pipe
            }
            else if (i % 2 == 1)
            {
                // printf("came into odd middle\n");
                dup2(fd[0], 0);  //inputut from pipe
                close(fd[1]);    // close outputut end of pipe
                dup2(fd2[1], 1); // outputut to transit
            }

            strcpy(temp, args[i]);
            if (redirection_check(temp))
            {
                redirect(part, j, args[i], home, last_wd);
            }
            // printf("now from exec\n");
            else
            {
                int z = execvp(part[0], part); // exec
                if (z < 0)
                    perror("Error: command not found\n");

                if (r == 0)
                    exit(0);
            }
            exit(0);
        }
        else
        {
            wait(NULL);

            if (i == 0)
            {
                close(fd[1]);
                if (input == 1)
                {
                    dup2(oldin, 0);
                    close(ifd);
                }
            }
            else if (i == count - 1)
            {
                if (i % 2 == 0)
                    close(fd2[0]);
                else
                    close(fd[0]);

                if (output == 1)
                {
                    dup2(oldout, 1);
                    close(ofd);
                }
            }
            else if (i % 2 == 0)
            {
                close(fd2[0]);
                close(fd[1]);
            }
            else if (i % 2 == 1)
            {
                close(fd[0]);
                close(fd2[1]);
            }
        }

        i++;
    }
}

int redirection_check(char command[])
{
    int count = 0;
    char *store[1000];
    int redirect_flag = 0;
    store[0] = strtok(command, " \n");
    while (store[count] != NULL)
    {
        count++;
        store[count] = strtok(NULL, " \n");
    }
        for (int i = 0; i < count; i++)
    {
        if (strcmp(store[i], ">") == 0)
            redirect_flag += 1;
        else if (strcmp(store[i], "<") == 0)
            redirect_flag += 1;
        else if (strcmp(store[i], ">>") == 0)
            redirect_flag == 1;
    }
    return redirect_flag;
}