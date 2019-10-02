#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

#include "global.h"
#include "my_utilities.h"
#include "my_utilities.c"
#include "pwd.h"
#include "pwd.c"
#include "cd.h"
#include "cd.c"
// #include "echo.h"
#include "echo.c"
#include "pinfo.c"
#include "pinfo.h"
#include "ls.h"
#include "ls.c"
#include "fore.c"
#include "fore.h"
#include "userdef1.c"
#include "redir.h"
#include "redir.c"
#include "exec_cmd.h"
#include "exec_cmd.c"

#define MAX 1001
#define LIST_MAX 2000

#define SHELL_ADDR "/home/pstalwalkar7/2-1/OperatingSystems/Shell/1"

pid_t Global_Pid;

void ctrlC_handler(int sig_num){
    signal(SIGINT,ctrlC_handler);
}

void ctrlZ_handler(int sig_num){
    if(getpid()!=Global_Pid){
        return;
    }  
    printf("runpid: %d\nProcess:%s\n",FORE.PID,FORE.S);

    kill(FORE.PID,SIGSTOP);
    signal(SIGTSTP,ctrlZ_handler);
}
int main()
{
    Global_Pid=getpid();
    signal(SIGTSTP,ctrlZ_handler);
    signal(SIGINT,ctrlC_handler);
    char user[MAX];
    char input[MAX];
    char dir[MAX];
    // char * tilde;
    char WorkingDir[MAX];
    struct utsname SYS;
    // cd("");    // kept to make ~ as start.
    restore_in;
    restore_out;
    int shell_pid = getpid();
    restore_in = dup(0);
    restore_out = dup(1);
    while (1)
    {
        strcpy(user, getenv("USER"));
        if (getcwd(dir, sizeof(dir)) == NULL)
        { // man doc: getcwd returns the abssolute directory path. Returns NULL if error.
            printf("Error! Current directory not found\n");
            exit(1);
        }
        else
        {
            int holder = uname(&SYS);
            if (holder < 0)
            {
                printf("Error! System name not found.\n");
                exit(1);
            }
            else
            {
                printf("<%s@%s:", user, SYS.sysname);
                if (TILDA(pwd()) == NULL)
                {
                    printf(">");
                }
                else
                {
                    printf("%s>", TILDA(pwd()));
                }
                signal(SIGCHLD, sigchld_handler);
                fgets(input, MAX, stdin);
                char input2[MAX];
                strcpy(input2, input);
                int valid_echo, valid_cd, valid_ls, valid_pinfo;
                char **cmds = calloc(MAX, sizeof(char *));
                char **cmdcopy = calloc(MAX, sizeof(char *));
                char **WORDS = calloc(MAX, sizeof(char *));
                char **PipedCmd = calloc(MAX, sizeof(char *));
                cmds = Parse(input, ";\n");
                cmdcopy = Parse(input2, ";\n");
                int pipe_len = 0;
                for (int i = 0; cmds[i]; i++)
                {
                    //WORDS=Parse(cmds[i]," ");      // ARRAY OF WORDS. so that each word can be accessed any way.
                    PipedCmd = Parse(cmds[i], "|");

                    for (int x = 0; PipedCmd[x]; x++)
                    {
                        // printf("cmd:%s\n",PipedCmd[x]);
                        pipe_len++;
                    }
                    if (pipe_len > 1)
                    {
                        printf("%d\n", pipe_len);
                        int S_IN = dup(0);
                        // L229 // POSS.
                        char **PipedCmdSplit = malloc(sizeof(char *) * MAX);
                        int ptr = 0;
                        // for (int x = 0; PipedCmd[x]; x++)
                        // {
                        //     write(restore_out, PipedCmd[x], strlen(PipedCmd[x]));
                        //     // printf("\n|||%s|||\n",PipedCmdSplit[x]);
                        // }
                        int p[2];
                        int prev_read = 0;
                        pid_t rid = 0;
                        int sta;
                        for (int x = 0; x < pipe_len; x++)
                        {
                            pipe(p);
                            int e_pid = fork();
                            if (e_pid < 0)
                            {
                                perror("error foriking\n");
                                break;
                            }
                            else if (e_pid == 0)
                            {
                                if (x == 0)
                                {
                                    dup2(p[1], 1);
                                    close(p[1]);
                                    PipedCmdSplit = redirIO(Parse(PipedCmd[x], " \t"));
                                    exec_cmd(Savior_convert(PipedCmdSplit, 0, 0));
                                    prev_read = p[0];
                                }
                                else if (x == pipe_len - 1)
                                {
                                    dup2(prev_read, 0);
                                    close(prev_read);
                                    close(p[0]);
                                    PipedCmdSplit = redirIO(Parse(PipedCmd[x], " "));
                                    exec_cmd(Savior_convert(PipedCmdSplit, 0, 0));
                                    prev_read = p[0];
                                }
                                else
                                {
                                    dup2(prev_read, 0);
                                    close(prev_read);
                                    close(p[0]);
                                    dup2(p[1], 1);
                                    close(p[1]);
                                    PipedCmdSplit = redirIO(Parse(PipedCmd[x], " \t"));
                                    exec_cmd(Savior_convert(PipedCmdSplit, 0, 0));
                                    prev_read = p[0];
                                }
                                exit(0);
                            }
                            else
                            {
                                // parent
                                waitpid(e_pid, &sta, 0);
                                close(p[1]);
                                prev_read = p[0];
                            }
                        }
                    }
                    else
                    { // no piping or empty.

                        WORDS = Parse(cmdcopy[i], " "); // ARRAY OF WORDS. so that each word can be accessed any way.
                        int restore_in = dup(0);
                        int restore_out = dup(1);
                        char **redir_rem = redirIO(WORDS); // remove the >> and get the job of redir done.

                        char redir_join[MAX];
                        redir_join[0] = '\0';
                        for (int x = 0; redir_rem[x]; x++)
                        {
                            strcat(redir_join, " ");
                            strcat(redir_join, redir_rem[x]);
                        }
                        // strcat(redir_join,NULL);     // NULL terminate.
                        exec_cmd(redir_join);

                        // exec_cmd(redir_rem);

                        dup2(restore_in, 0);
                        dup2(restore_out, 1);
                        close(restore_in);
                        close(restore_out);
                    }
                }
            }
        }
    }
}