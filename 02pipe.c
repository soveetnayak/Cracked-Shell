#include "headers.h"

void main_pipe(char *args[], int count, char home[], char last_wd[])
{
    int i = 0;

    int fd_even[2];
    int fd_odd[2];

    int input = 0;
    int output = 0;

    char arg[10000], temp[10000];
    while (i < count)
    {
        int oldout, oldin;
        int check;
        strcpy(arg, args[i]);

        char *store[10000];

        oldout = dup(1);
        oldin = dup(0);

        int count = 0;
        store[count] = strtok(arg, " \n");
        while (store[count] != NULL)
        {
            count++;
            store[count] = strtok(NULL, " \n");
        }

        if (i % 2 == 0)
            check = pipe(fd_even);
        else
            check = pipe(fd_odd);

        if (check < 0)
        {
            printf("Error: Pipe could not be created\n");
            return;
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
                dup2(fd_even[1], 1); //output
                close(fd_even[0]);
            }
            else if (i == count - 1)
            {
                if (i % 2 == 1)
                {
                    dup2(fd_even[0], 0); //input
                }
                else
                {
                    dup2(fd_odd[0], 0); //input
                }
            }
            else if (i % 2 == 0)
            {
                dup2(fd_odd[0], 0);  
                close(fd_even[0]);   
                close(fd_odd[1]);    
                dup2(fd_even[1], 1); 
            }
            else if (i % 2 == 1)
            {
                dup2(fd_even[0], 0); 
                close(fd_odd[0]);    
                close(fd_even[1]);   
                dup2(fd_odd[1], 1);  
            }

            strcpy(temp, args[i]);
            if (redirection_check(temp))
            {
                redirect(store, count, args[i], home, last_wd);
            }
            else
            {
                if (execvp(store[0], store) < 0)
                    printf("Error: Command not found\n");
            }
            exit(0);
        }
        else
        {
            if (wait(NULL) < 0)
                printf("Error: wait failed\n");

            if (i == 0)
            {
                close(fd_even[1]);
            }
            else if (i == count - 1)
            {
                if (i % 2 == 0)
                    close(fd_odd[0]);
                else
                    close(fd_even[0]);
            }
            else if (i % 2 == 0)
            {
                close(fd_odd[0]);
                close(fd_even[1]);
            }
            else if (i % 2 == 1)
            {
                close(fd_even[0]);
                close(fd_odd[1]);
            }
        }

        i++;
    }
    dup2(STDIN_FILENO, 0);
    dup2(STDOUT_FILENO, 1);
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
            redirect_flag += 1;
    }
    return redirect_flag;
}