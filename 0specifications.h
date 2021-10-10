#ifndef __SPECIFICATIONS_H__
#define __SPECIFICATIONS_H__

//01 02 03
void redirect(char *store[], int count, char *command, char home[], char last_wd[]);
void loop(char *store[], int count, char home[], char last_wd[]);

void main_pipe(char *args[], int count, char home[], char last_wd[]);
int redirection_check(char command[]);

//04
void printjobs(char *store[], int count);
void sig(int job_no, int sig_no);
void fg(char *store[]);
void bg(char *store[]);
void delete_process(int id);


//05
void ctrl_z();
void ctrl_c();
//ctrl_d is implemented within main.c

//bonus
void replay(char *store[], int count, char home[], char last_wd[]);
void baywatch(char *store[], int count);

#endif