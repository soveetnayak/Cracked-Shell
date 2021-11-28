#include "headers.h"

int a_flag = 0;
int l_flag = 0;
char list_dir[100][10000];

void function_ls(char *store[], int count, char *cwd, char *home)
{
    a_flag = 0;
    l_flag = 0;
    // printf("Heree");
    for (int i = 0; i < 100; i++)
    {
        strcpy(list_dir[i], "Empty_Dir");
    }
    if (count == 1)
    {
        ls_and_lsa(cwd, home);
    }
    if (count > 1)
    {
        int i = 1;

        while (i != count)
        {
            if (strcmp(store[i], "-a") == 0)
            {
                a_flag = 1;
            }
            else if (strcmp(store[i], "-l") == 0)
            {
                l_flag = 1;
            }
            else if (strcmp(store[i], "-al") == 0)
            {
                a_flag = 1;
                l_flag = 1;
            }
            else if (strcmp(store[i], "-la") == 0)
            {
                a_flag = 1;
                l_flag = 1;
            }
            else
            {

                int j = 0;
                while (strcmp(list_dir[j], "Empty_Dir") != 0)
                {
                    j++;
                }
                strcpy(list_dir[j], store[i]);
            }
            i++;
        }
        if (l_flag == 0)
        {
            ls_and_lsa(cwd, home);
        }
        else
        {
            lsl(cwd, home);
        }
    }
}

void ls_and_lsa(char *cwd, char *home)
{
    // printf("Heree");
    if (strcmp(list_dir[0], "Empty_Dir") == 0)
    {
        struct dirent *entry;
        DIR *dir = opendir(cwd);
        if (!dir)
            if (!dir)
            {
                if (errno = ENOENT)
                {
                    //If the directory is not found
                    perror("Directory doesn't exist");
                }
                else
                {
                    //If the directory is not readable then throw error and exit
                    perror("Unable to read directory");
                }
                exit(1);
            }
        while ((entry = readdir(dir)) != NULL)
        {
            if (!a_flag && entry->d_name[0] == '.')
                continue;
            if (/*entry->d_type == DT_DIR*/1)
            {
                printf("%s ", entry->d_name);
            }
        }
        printf("\n");
    }
    else
    {

        fflush(stdout);
        int i = 0;
        while (strcmp(list_dir[i], "Empty_Dir") != 0)
        {
            char path[10000];
            strcpy(path, list_dir[i]);
            if (list_dir[i][0] == '~')
            {
                strcpy(path, "");
                strcpy(path, home);
                strcat(path, &list_dir[i][1]);
            }
            strcpy(list_dir[i], path);
            struct dirent *entry;
            DIR *dir = opendir(list_dir[i]);
            if (!dir)
                if (!dir)
                {
                    if (errno = ENOENT)
                    {
                        //If the directory is not found
                        perror("Directory doesn't exist");
                    }
                    else
                    {
                        //If the directory is not readable then throw error and exit
                        perror("Unable to read directory");
                    }
                }
                else
                {
                    while ((entry = readdir(dir)) != NULL)
                    {
                        if (!a_flag && entry->d_name[0] == '.')
                            continue;
                        if (/*entry->d_type == DT_DIR*/1)
                        {
                            printf("%s ", entry->d_name);
                        }
                    }
                    printf("\n");
                }
            i++;
        }
    }
}

void lsl(char *cwd, char *home)
{
    if (strcmp(list_dir[0], "Empty_Dir") == 0)
    {
        strcpy(list_dir[0], cwd);
    }

    int i = 0;
    while (strcmp(list_dir[i], "Empty_Dir") != 0)
    {

        struct stat s;
        char path[10000];
        char perms[100];
        // strcpy(path, "");
        // strcat(path, home);
        // strcat(path, "/");
        strcpy(path, list_dir[i]);
        if (list_dir[i][0] == '~')
        {
            strcpy(path, "");
            strcpy(path, home);
            strcat(path, &list_dir[i][1]);
        }

        DIR *d;
        struct dirent **entry;

        int noOfFiles = scandir(path, &entry, NULL, alphasort);
        if (noOfFiles < 0)
        {
            //If the directory is not found
            perror("Directory doesn't exist\n");
        }
        else
        {
            int j = 0;
            while (j < noOfFiles)
            {

                char name[10000];
                strcpy(name, entry[j]->d_name);
                char location[10000];
                strcpy(location, "");
                strcat(location, list_dir[i]);
                strcat(location, "/");
                strcat(location, name);
                // printf("%s\n", location);
                if (!a_flag && name[0] == '.')
                {
                    j++;
                    continue;
                }
                if (stat(location, &s) == -1)
                {
                    printf("Directory not found\n");
                }
                else
                {
                    S_ISDIR(s.st_mode) ? strcat(perms, "d") : strcat(perms, "-");
                    (s.st_mode & S_IRUSR) ? strcat(perms, "r") : strcat(perms, "-");
                    ;
                    (s.st_mode & S_IWUSR) ? strcat(perms, "w") : strcat(perms, "-");
                    (s.st_mode & S_IXUSR) ? strcat(perms, "x") : strcat(perms, "-");
                    (s.st_mode & S_IRGRP) ? strcat(perms, "r") : strcat(perms, "-");
                    (s.st_mode & S_IWGRP) ? strcat(perms, "w") : strcat(perms, "-");
                    (s.st_mode & S_IXGRP) ? strcat(perms, "x") : strcat(perms, "-");
                    (s.st_mode & S_IROTH) ? strcat(perms, "r") : strcat(perms, "-");
                    (s.st_mode & S_IWOTH) ? strcat(perms, "w") : strcat(perms, "-");
                    (s.st_mode & S_IXOTH) ? strcat(perms, "x") : strcat(perms, "-");
                }
                printf("%s", perms);
                printf("%2ld ", (long)s.st_nlink);
                struct passwd *u;
                struct group *g;
                u = getpwuid(s.st_uid);
                g = getgrgid(s.st_gid);

                printf("%8s ", u->pw_name);
                printf("%8s", g->gr_name);
                printf("%8ld ", (long)s.st_size);

                struct tm *t;
                t = localtime(&s.st_mtime);

                char *mnth[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

                printf("%s ", mnth[t->tm_mon]);

                char time[100];
                strcpy(time, "");
                strftime(time, 24, "%d    %H:%M", localtime(&(s.st_ctime)));
                printf("%s ", time);
                printf("%s", name);
                printf("\n");
                strcpy(perms, "");
                j++;
            }
        }
        printf("\n");
        i++;
    }
}