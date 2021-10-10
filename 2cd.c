#include "headers.h"

void function_cd(char *store[], int count, char *home, char *last_wd)
{
    if (count > 2)
    {
        printf("Too many arguments.\n");
        return;
    }
    else if (count == 2)
    {
        char store2[10000];
        strcpy(store2, store[1]);
        if (strcmp(store2, "~") == 0)
        {
            getcwd(last_wd, 10000);
            chdir(home);
            return;
        }
        else if (strcmp(store2, "-") == 0)
        {
            if (strcmp(last_wd, "") == 0)
            {
                printf("No previous working directory.\n");
                return;
            }
            strcpy(store2, last_wd);
        }

        if (store2[0] == '~' && strlen(store[1]) > 1)
        {
            store2[0] = '.';
            printf("%s\n", store2);
        }
        getcwd(last_wd, 10000);
        if (chdir(store2) == -1)
        {
            printf("cd: %s: No such file or directory\n", store[1]);
            return;
        }
        return;
    }
    else
    {
        chdir(home);
        getcwd(last_wd, 10000);
    }
}
// /home/soveet/Desktop\0
// /home/soveet/Desktop/Assignment\0