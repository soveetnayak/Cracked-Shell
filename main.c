#include "headers.h"
char home[10000];
char last_wd[10000] = "";
char *temparr[10000] = {NULL};

int main()
{
    /*********************************/
    strcpy(cur_process.name, "invalid");
    cur_process.pid = -1;
    shellid = getpid();
    /*********************************/

    /*********************************/
    green();
    printf("*************************************************************\n");
    red();
    printf("                    **Cracked Shell**            \n");
    green();
    printf("*************************************************************\n");
    reset();
    /*********************************/
    if (getcwd(home, sizeof(home)) == NULL)
    {
        perror("getcwd() error");
        exit(0);
    }
    processes_count = 0;

    signal(SIGCHLD, check_process);
    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);

    while (1)
    {
        int pipe_flag = 0;
        int redirect_flag = 0;

        prompt(home);
        char str[10000];
        char *result;
        result = gets(str);
        if (result == NULL)
        {
            //Ctrl-D detected
            printf("\n");
            red();
            printf("Exiting Cracked Shell...");
            reset();
            printf("\n");
            return 0;
        }

        int length = strlen(str);
        //Formatting the input
        for (int i = 0; i < length; i++)
        {
            if (str[0] == ' ')
            {
                //removing all space at the start
                for (i = 0; i < (length - 1); i++)
                    str[i] = str[i + 1];
                str[i] = '\0';
                length--;
                i = -1;
                continue;
            }
            if (str[i] == ' ' && str[i + 1] == ' ')
            {
                int j;
                for (j = i; j < (length - 1); j++)
                {
                    char temp = str[j + 1];
                    str[j] = temp;
                }
                str[j] = '\0';
                length--;
                i--;
            }
        }

        const char s[2] = ";";
        char *token = strtok(str, s);
        char *colonize[10000] = {NULL};
        int z = 0;
        while (token != NULL)
        {
            colonize[z] = token;
            z++;
            token = strtok(NULL, s);
        }
        z = 0;
        while (colonize[z] != NULL)
        {
            //printf("%s\n", token);
            char *temp = colonize[z];
            char command[10000];
            strcpy(command, temp);

            char command2[10000];
            strcpy(command2, temp);

            char *token2 = strtok(command2, " ");
            char *store[10000] = {NULL};
            int count = 0;

            while (token2 != NULL)
            {
                store[count] = token2;
                count++;
                token2 = strtok(NULL, " \n");
            }

            //Check piping
            for (int i = 0; i < count; i++)
            {
                if (strcmp(store[i], "|") == 0)
                {
                    pipe_flag = 1;
                    break;
                }
            }
            if (pipe_flag)
            {
                int i = 0;
                temparr[i] = strtok(command, "|");
                while (temparr[i] != NULL)
                {
                    i++;
                    temparr[i] = strtok(NULL, "|");
                }
                main_pipe(temparr, i, home, last_wd);
                pipe_flag = 0;
                z++;
                continue;
            }

            //Check redirection
            for (int z = 0; z < count; z++)
            {
                if (strcmp(store[z], ">") == 0 || strcmp(store[z], "<") == 0 || strcmp(store[z], ">>") == 0)
                {
                    redirect_flag = 1;
                }
            }
            if (redirect_flag == 1)
            {
                redirect(store, count, command, home, last_wd);
                redirect_flag = 0;
                z++;
                continue;
            }

            int repeat = 1;
            if (strcmp(store[0], "repeat") == 0)
            {

                repeat = atoi(store[1]);
                for (int i = 0; i < count; i++)
                {
                    store[i] = store[i + 2];
                }
                count -= 2;
            }

            for (int i = 0; i < repeat; i++)
            {
                if (strcmp(store[count - 1], "&") == 0)
                {

                    store[count - 1] = NULL;
                    function_background(store, count - 1);
                }
                else if (strcmp(store[0], "cd") == 0)
                {

                    function_cd(store, count, home, last_wd);
                }
                else if (strcmp(store[0], "echo") == 0)
                {

                    function_echo(store);
                }
                else if (strcmp(store[0], "pwd") == 0)
                {

                    function_pwd();
                }
                else if (strcmp(store[0], "pinfo") == 0)
                {

                    function_pinfo(store, count, home);
                }
                else if (strcmp(store[0], "ls") == 0)
                {

                    char cwd[10000];
                    getcwd(cwd, sizeof(cwd));
                    function_ls(store, count, cwd, home);
                }
                else if (strcmp(store[0], "jobs") == 0)
                {
                    printjobs(store, count);
                }
                else if (strcmp(store[0], "sig") == 0)
                {
                    sig(atoi(store[1]), atoi(store[2]));
                }
                else if (strcmp(store[0], "fg") == 0)
                {
                    fg(store);
                }
                else if (strcmp(store[0], "bg") == 0)
                {
                    bg(store);
                }
                else if (strcmp(store[0], "baywatch") == 0)
                {
                    baywatch(store, count);
                }
                else if (strcmp(store[0], "replay")==0 )
                {
                    replay(store, count, home, last_wd);
                }
                else if (strcmp(store[0], "exit") == 0)
                {
                    printf("\n");
                    red();
                    printf("Exiting Cracked Shell...");
                    reset();
                    printf("\n");
                    exit(0);
                }
                else
                {

                    function_foreground(store);
                }
            }
            z++;
            //printf("%s", token);
        }
    }
}
