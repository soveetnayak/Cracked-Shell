#include "headers.h"

void function_pinfo(char *store[], int count, char *home)
{

        pid_t pid;
        if (count > 2)
        {
                printf("pinfo: Too many arguments\n");
                return;
        }
        else if (count == 1)
        {

                pid = getpid();
        }
        else
        {
                char *str = NULL;
                pid = (int)strtol(store[1], &str, 10);

                if (!(str == NULL || strcmp("", str) == 0))
                {
                        printf("pinfo: Must be a number\n");
                        return;
                }
        }
        char file[10000];
        sprintf(file, "/proc/%d/stat", pid); //For status, memory
        FILE *fp;
        int fp1 = open(file, O_RDONLY);
        char buffer[10000];
        if (fp1 == -1)
        {
                printf("pinfo: Invalid PID\n");
                return;
        }
        else
        {
                char stat;
                long int memory;
                int pid_x;
                int tpgid;
                fp = fopen(file, "r");
                fscanf(fp, "%d %*s %c %*d %*d %*d %*d %d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %ld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &pid_x, &stat, &tpgid, &memory);
                fclose(fp);
                printf("pid -- %d\n", pid);
                printf("Process Status -- %c", stat);
                if (tpgid == pid_x)
                {
                        if (stat == 'R' || stat == 'S')
                                printf("+");
                }
                printf("\n");
                printf("Memory -- %ld {Virtual Memory}\n", memory);

                sprintf(file, "/proc/%d/exe", pid);
                readlink(file, buffer, sizeof(buffer));

                char output[10000];
                strcpy(output, buffer);
                char symbol[2] = "~";
                int i = 0, j = 0, flag = 0, start = 0;
                while (home[j] != '\0')
                {
                        if (home[j] == buffer[i])
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
                        for (j = strlen(home); j < strlen(buffer); j++)
                        {
                                output[i] = buffer[j];
                                i++;
                        }

                        // print the final string
                        output[i] = '\0';
                }

                printf("Executable Path -- %s\n", output);
        }
}