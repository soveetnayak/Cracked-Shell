#include "headers.h"

void redirect(char *store[], int count, char *string, char home[], char last_wd[])
{
    int append = 0, inp = 0, outp = 0;
    int status;
    char tempc[1000];
    for (int i = 0; i < count; i++)
    {
        strcpy(tempc, store[i]);
        if (tempc[0] == '>')
            outp += 1;
        else if (tempc[0] == '<')
            inp += 1;

        if (tempc[0] == '>' && tempc[1] == '>')
            append += 1;
    }
    char *command[10000];
    char input[10000], output[10000];

    strcpy(output, "invalid");
    strcpy(input, "invalid");

    int fd1 = -1;
    int fd2 = -1;

    char delim[5];
    int k;
    if (append == 1)
        strcpy(delim, ">>");
    else
        strcpy(delim, ">");

    //echo "hello" > output.txt
    //sort < file1.txt > lines_sorted.txt

    k = 0;
    char *chk = strtok(string, delim);
    while (chk != NULL)
    {
        command[k++] = chk;
        chk = strtok(NULL, delim);
    }
    // sort < file1.txt, lines_sorted.txt
    char *temp[10000];
    if (k == 2)
    {

        strcpy(output, command[1]);
        temp[0] = strtok(output, " \n");
        strcpy(output, temp[0]);
    }
    // output = lines_sorted.txt

    int l = 0;
    temp[0] = strtok(command[0], "<");
    while (temp[l] != NULL)
    {
        l++;
        temp[l] = strtok(NULL, "<");
    }
    //sort, file1.txt
    if (l == 2)
    {
        char *temp0;
        strcpy(input, temp[1]);
        temp0 = strtok(input, " \n");
        strcpy(input, temp0);
    }
    //input = file1.txt

    k = 0;
    char *from[10000];
    from[0] = strtok(temp[0], " \n");
    while (from[k] != NULL)
    {
        k++;
        from[k] = strtok(NULL, " \n");
    }

    if (inp > 0 && (outp == 0 && append == 0)) //INPUT REDIRECTION
    {
        int in = dup(STDIN_FILENO);
        int pid = fork();
        fd1 = open(input, O_RDONLY);

        if (pid == 0)
        {
            if (fd1 < 0)
                perror("File doesn't exist\n");
            else
            {
                dup2(fd1, 0);
                loop(from, k, home, last_wd);
                dup2(in, 0);
                exit(0);
            }
        }
        else
            while (wait(&status) != pid)
                ;
    }
    else if ((outp > 0 || append > 0) && inp == 0) //OUTPUT REDIRECTION
    {
        int out = dup(STDOUT_FILENO);
        int pid = fork();
        if (append == 1)
        {

            fd1 = open(output, O_APPEND | O_WRONLY | O_CREAT, 0644);
        }
        else
            fd1 = open(output, O_WRONLY | O_TRUNC | O_CREAT, 0644);

        dup2(fd1, 1);

        if (pid == 0)
        {
            loop(from, k, home, last_wd);
            exit(0);
        }
        else
        {
            while (wait(&status) != pid)
                ;
            dup2(out, 1);
            close(fd1);
        }
    }
    else
    {
        //Both

        int in = dup(STDIN_FILENO);
        int out = dup(STDOUT_FILENO);

        int pid = fork();

        //Input
        fd1 = open(input, O_RDONLY);

        //Output
        if (append == 0)
            fd2 = open(output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        else
            fd2 = open(output, O_APPEND | O_WRONLY | O_CREAT, 0644);

        dup2(fd2, 1);

        if (pid == 0)
        {
            if (fd1 < 0)
                perror("File doesn't exist\n");
            else
            {
                dup2(fd1, 0);
                loop(from, k, home, last_wd);
                dup2(in, 0);
            }
            exit(0);
        }
        else
        {
            while (wait(&status) != pid)
                ;

            dup2(out, 1);
            close(fd1);
        }
    }
}

void loop(char *store[], int count, char home[], char last_wd[])
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
    else if (strcmp(store[0], "replay") == 0)
    {
        replay(store, count, home, last_wd);
    }
    else if (strcmp(store[0], "exit") == 0)
    {
        exit(0);
    }
    else
    {

        function_foreground(store);
    }
}