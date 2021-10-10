#include "headers.h"

char *function_pwd ()
{
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) == NULL) 
    {
       perror("getcwd() error");
       exit(0);
    }
    printf("%s\n", cwd);
}