#include "headers.h"

void replay(char *store[], int count, char home[], char last_wd[])
{
    int com = 0, inter = 0, per = 0;
    int comp = 0, interp = 0, perp = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(store[i], "-command") == 0)
        {
            comp = i;
            com++;
        }
        else if (strcmp(store[i], "-interval") == 0)
        {
            interp = i;
            inter++;
        }
        else if (strcmp(store[i], "-period") == 0)
        {
            perp = i;
            per++;
        }
    }

    if (com == 1 && inter == 1 && per == 1)
    {

        int i;
        char *command[1000];
        for (i = comp + 1; i < interp; i++)
        {
            command[i - comp - 1] = store[i];
            printf("%s\n", command[i - comp - 1]);
        }
        command[i - comp - 1] = NULL;

        int interval = atoi(store[interp + 1]);
        int period = atoi(store[perp + 1]);
        if(interval>period)
        {
            printf("Interval cannot be greater than period\n");
            return;
        }
        for (int i = 0; i < period; i += interval)
        {
            if (i > period - interval)
            {
                sleep(period - i);
            }
            else
            {
                sleep(interval);
                loop(command, interp - comp - 1, home, last_wd);
                fflush(stdout);
            }
        }
    }
    else
    {
        printf("Invalid arguments\n");
    }
}