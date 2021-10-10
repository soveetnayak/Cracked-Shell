#include "headers.h"

void baywatch(char *store[], int count)
{
    if (count != 4 && strcmp(store[1], "-n") == 0)
    {
        printf("Error: baywatch requires exactly 4 arguments.\n");
        return;
    }
    int interval = atoi(store[2]);

    if (interval <= 0)
    {
        printf("Error: interval must be a positive integer.\n");
        return;
    }
    if (strcmp(store[3], "interrupt") == 0)
    {
        FILE *file;
        fd_set readfds;
        FD_ZERO(&readfds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        static struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON);

        char c;
        printf("CPU0\tCPU1\tCPU2\tCPU3\tCPU4\tCPU5\tCPU6\tCPU7\n");
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        while (1)
        {

            FD_SET(STDIN_FILENO, &readfds);

            if (select(1, &readfds, NULL, NULL, &timeout))
            {
                c = getchar();
                if (c == 'q')
                {
                    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                    return;
                }
            }

            file = fopen("/proc/interrupts", "r");
            if (file == NULL)
            {
                printf("Error: could not open /proc/interrupts.\n");
                return;
            }

            char line[256];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                if (strstr(line, "i8042") != NULL)
                {
                    char *temp[100];
                    int i = 0;
                    temp[0] = strtok(line, " ");
                    while (temp[i] != NULL)
                    {
                        i++;
                        temp[i] = strtok(NULL, " ");
                    }
                    for (int i = 1; i < 9; i++)
                    {
                        printf("%s\t", temp[i]);
                    }
                    printf("\n");
                    fflush(stdout);
                }
            }
            fclose(file);
            sleep(interval);
        }
    }
    else if (strcmp(store[3], "newborn") == 0)
    {
        FILE *file;
        fd_set readfds;
        FD_ZERO(&readfds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        static struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        char c;
        while (1)
        {

            FD_SET(STDIN_FILENO, &readfds);

            if (select(1, &readfds, NULL, NULL, &timeout))
            {
                c = getchar();
                if (c == 'q')
                {
                    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                    return;
                }
            }

            file = fopen("/proc/loadavg", "r");
            if (file == NULL)
            {
                printf("Error: could not open /proc/loadavg.\n");
                return;
            }

            char line[256];
            fgets(line, sizeof(line), file);
            int i = 0;
            char *temp[10];
            temp[0] = strtok(line, " \n");
            while (temp[i] != NULL)
            {
                i++;
                temp[i] = strtok(NULL, " \n");
            }
            printf("%s\n", temp[i - 1]);
            sleep(interval);
        }
    }
    else if (strcmp(store[3], "dirty") == 0)
    {
        FILE *meminfo;
        fd_set readfds;
        FD_ZERO(&readfds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        char c;

        static struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        while (1)
        {

            FD_SET(STDIN_FILENO, &readfds);

            if (select(1, &readfds, NULL, NULL, &timeout))
            {
                c = getchar();
                if (c == 'q')
                {
                    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                    return;
                }
            }

            meminfo = fopen("/proc/meminfo", "r");
            if (meminfo == NULL)
            {
                printf("Error: could not open /proc/meminfo.\n");
                return;
            }

            char line[256];
            while (fgets(line, sizeof(line), meminfo))
            {
                int val;
                if (sscanf(line, "Dirty: %d kB", &val) == 1)
                {
                    fclose(meminfo);
                    printf("%d kB\n", val);
                }
            }

            sleep(interval);
        }
    }
    else
    {
        printf("Error: invalid argument.\n");
        return;
    }
}
