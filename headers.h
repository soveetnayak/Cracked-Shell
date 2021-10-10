#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#include <termios.h>

/******************************************************************************/
typedef struct process_info process;

struct process_info {
    pid_t pid;
    int job_no;
    char name[10000];
};

struct process_info processes[10000];
struct process_info cur_process;

int processes_count;
int job_count;

int shellid;
/******************************************************************************/

#include "prompt.h"
#include "2pwd.h"
#include "2echo.h"
#include "2cd.h"
#include "3ls.h"
#include "4foreground.h"
#include "4background.h"
#include "5pinfo.h"
#include "6checkbg.h"
#include "colors.h"
#include "0specifications.h"


#endif