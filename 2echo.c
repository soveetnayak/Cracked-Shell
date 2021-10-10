#include "headers.h"

void function_echo(char *store[])
{

    int i = 1;
    while (store[i] != NULL)
    {
        green();
        printf("%s ", store[i]);
        i++;
        reset();
    }
    printf("\b\n");
}