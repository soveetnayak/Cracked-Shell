#include "headers.h"

void prompt(char *home)
{
        char systemname[HOST_NAME_MAX];
        char username[LOGIN_NAME_MAX];
        gethostname(systemname, HOST_NAME_MAX);
        getlogin_r(username, LOGIN_NAME_MAX);

        char cwd[10000];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
                perror("getcwd() error");
                exit(0);
        }

        char output[10000];
        strcpy(output, cwd);
        char symbol[2] = "~";
        int i = 0, j = 0, flag = 0, start = 0;
        while (home[j] != '\0')
        {
                if (home[j] == cwd[i])
                {
                        i++;
                        j++;
                }
                else
                {
                        flag = 1;
                        break;
                        //not the same substring
                }
        }

        if (!flag)
        {
                strcpy(output, "");
                output[0] = symbol[0];
                i = 1;
                // copy remaining portion of the input string "str"
                for (j = strlen(home); j < strlen(cwd); j++)
                {
                        output[i] = cwd[j];
                        i++;
                }

                // print the final string
                output[i] = '\0';
        }
        yellow();
        printf("<%s@%s:%s>", username, systemname, output);
        reset();
}
