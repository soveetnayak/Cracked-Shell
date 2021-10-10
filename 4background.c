#include "headers.h"

int comparator(const void *p, const void *q) 
{
    char * l ;
    l = ((process*)p)->name;
    char * r ;
    r = ((process*)q)->name; 
    if(strcmp(r,l)>0)
    {
        return -1;
    }
    else
        return 1;
}

void function_background(char *store[],int count)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        printf("Error in fork()\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // child process
        int flag = execvp(store[0],store);
        if (flag == -1)
        {
            printf("Error in execvp()\n");
            exit(1);
        }
    }
    else
    {
        // parent process
        
        //printf("%s\n",store[0]);
        processes_count++;
        job_count++;
        processes[processes_count].pid = pid;
        processes[processes_count].job_no = job_count;
        strcpy(processes[processes_count].name,store[0]);
        printf("pid: %d\n",pid);
        printf("job_no: %d\n",job_count);
       
    }

}