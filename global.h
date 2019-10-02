#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>

#define MAX 1001
#define LIST_MAX 2000

#define SHELL_ADDR "/home/pstalwalkar7/2-1/OperatingSystems/Shell/1"
struct job_sp{
    pid_t PID;
    char S[MAX];
}job_sp;
struct job_sp Jobs[MAX];
int Job_pos=0;
int restore_in;
int restore_out;