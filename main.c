#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include <sys/utsname.h>
#include "my_utilities.h"        // MY OBSERVATIONS ON THE NATURE OF INCLUDE: <> can be included multiple times. User defined cant. if 2 files use a common file say
                                // util.h and util.c . U can circumvent repition problem: in 1st, rewrite what is needed for .c to work, from .h. Don t include .h in 1st. Include in 2nd.
#include "my_utilities.c"
#include "pwd.h"
#include "pwd.c"
#include "cd.h"
#include "cd.c"
// #include "echo.h"
#include "echo.c"
#include "ls.h"
#include "pinfo.c"
#include "pinfo.h"
#include "ls.c"
#include "fore.c"
#include "fore.h"
#define MAX 1001
#define LIST_MAX 2000
#define SHELL_ADDR "/home/pstalwalkar7/2-1/OperatingSystems/Shell/1"
int main(){
    char user[MAX];
    char input[MAX];
    char dir[MAX];
    // char * tilde;
    char WorkingDir[MAX];
    struct utsname SYS;
    while(1){
        strcpy(user,getenv("USER"));
        if(getcwd(dir,sizeof(dir))==NULL){   // man doc: getcwd returns the abssolute directory path. Returns NULL if error.
            printf("Error! Current directory not found\n");
            exit(1);
        }
        else{
            int x=uname(&SYS);
            if(x<0){
                printf("Error! System name not found.\n");
                exit(1);
            }
            else{
                printf("<%s@%s:",user,SYS.sysname);
                if(TILDA(pwd())==NULL){
                    printf(">");
                }
                else{
                    printf("%s>",TILDA(pwd()));
                }
                signal(SIGCHLD,sigchld_handler);
                fgets(input,MAX,stdin);
                int valid_echo,valid_cd,valid_ls,valid_pinfo;
                char * cmd = strtok(input,";");      // returns 1st group of characters constituting a command.  The next delimiter found is conseidered as start of the next token.
                while(cmd!=NULL){                       // no more tokens are found. so end.
                    cmd=rem_leading_spaces(cmd);
                    valid_cd=(strlen(cmd)>=3 && cmd[0]=='c' && cmd[1]=='d' && (cmd[2]==' ' || cmd[2]=='\n') )||(strlen(cmd)==2 && cmd[0]=='c' && cmd[1]=='d');
                    valid_echo=strlen(cmd)==4 && cmd[0]=='e' && cmd[1]=='c' && cmd[2]=='h' && cmd[3]=='o';
                    valid_echo=valid_echo ||(strlen(cmd)>=5 && cmd[0]=='e'  && cmd[1]=='c'  && cmd[2]=='h' && cmd[3]=='o' && (cmd[4]==' ' || cmd[4]=='\n'));
                    valid_ls=strlen(cmd)==2 && cmd[0]=='l'  && cmd[1]=='s';
                    valid_ls=valid_ls || strlen(cmd)>2 && cmd[0]=='l'  && cmd[1]=='s' &&  (cmd[2]=='\n'  || cmd[2]==' ');
                    valid_pinfo=(strlen(cmd)==5 && cmd[0]=='p' && cmd[1]=='i' && cmd[2]=='n' && cmd[3]=='f' && cmd[4]=='o') ||
                                (strlen(cmd)>=5 && cmd[0]=='p' && cmd[1]=='i' && cmd[2]=='n' && cmd[3]=='f' && cmd[4]=='o' && (cmd[5]==' ' || cmd[5]=='\n'));
                    if(str_match(cmd,"pwd")){
                        strcpy(WorkingDir,pwd());
                        if(!WorkingDir){
                            printf("Error!\n");
                        }
                        else{
                            printf("%s\n",WorkingDir);
                        }
                    }
                    else if(valid_cd){ // valid cd
                        char To_dir[MAX];
                        int letter=MAX+1,sp=MAX+2;
                        int j=0;
                        for(int i=3;i<strlen(cmd);i++){
                            if(cmd[i]==' '){
                                if(letter!=MAX+1){
                                    sp=i;
                                }
                                else{
                                    continue;
                                }
                            }
                            else if(cmd[i]!='\n'){
                                // printf("%d:%d\n",i,j);
                                letter=i;
                                To_dir[j++]=cmd[i];
                            }
                            if(sp<letter){    // a letter after a space with a catch. Space is init to MAX+2 and a space location is rec only if a letter has been passed
                                printf("bash: cd: Too many arguments\n");
                                break;
                            }
                        }
                        To_dir[j]='\0';
                        cd(To_dir);
                    }
                    else if(valid_echo){
                        cmd=rem_leading_spaces(cmd+4);
                        // printf("%s",cmd);
                        echo(cmd);
                    }
                    else if(valid_ls){
                        for(int i=0;i<MAX;i++){
                            if(input[i]=='\n'){
                                input[i]='\0';
                                break;
                            }
                        }
                        for(int i=0;i<MAX;i++){
                            if(cmd[i]=='\n'){
                                cmd[i]='\0';
                                break;
                            }
                        }
                        cmd=rem_leading_spaces(cmd+2);
                        ls(cmd); 
                    }
                    else if(valid_pinfo){
                        cmd=rem_leading_spaces(cmd+5);
                        for(int i=0;i<MAX;i++){
                            if(cmd[i]=='\n'){
                                cmd[i]='\0';
                                break;
                            }
                        }
                        pinfo(cmd);
                    }
                    // else if((strlen(cmd)==4 && cmd[0]=='e' && cmd[1]=='x' && cmd[2]=='i' && cmd[3]=='t') || strlen(cmd)>=5 && cmd[0]=='e' && cmd[1]=='x' && cmd[2]=='i' && cmd[3]=='t' 
                    // && (cmd[4]=='\n' || cmd[4]==' ')){
                    //     printf("Shell is exiting! Goodbye!\n");
                    //     return 0;
                    // }
                    else{
                        for(int i=0;i<MAX;i++){
                            if(cmd[i]=='\n'){
                                cmd[i]='\0';
                                break;
                            }
                        }
                        int fg=1;
                        if(strlen(cmd)>1){
                            for(int i=0;cmd[i];i++){
                                if(cmd[i]=='&'){
                                    fg=0;
                                }
                            }
                            if(fg){
                                // printf("SSS\n");
                                foreground(cmd);
                            }
                            else{
                                // printf("GGG\n");
                                background(cmd);
                                // int status;
                                // char *S[LIST_MAX];
                                // char *WORD=strtok(cmd," ");
                                // int position_1=0;
                                // while(WORD!=NULL){
                                //     S[position_1++]=WORD;
                                //     WORD=strtok(NULL," ");
                                // }    
                                // S[position_1++]="\0";
                                // pid_t pid2=fork();
                                // if(pid2<0){
                                //     printf("Unable to fork");
                                // }
                                // else if( !pid2 && execvp(S[0],S)<0){
                                //     perror("Error!Unable to run the command.\n");
                                // }
                                // else{
                                //     waitpid(pid2,&status,0);
                                //     if(!status){
                                //         printf("\n%s with pid %d exited\n",WORD,pid2);
                                //     }
                                // }
                            }
                        }

                        // int status;
                        // char *S[LIST_MAX];
                        // pid_t pid1=fork();
                        // char *WORD=strtok(cmd," ");
                        // int position_1=0;
                        // while(WORD!=NULL){
                        //     S[position_1++]=WORD;
                        //     WORD=strtok(NULL," ");
                        // }    
                        // S[position_1++]="\0";
                        // if(pid1<0){
                        //     printf("Unable to fork");
                        // }
                        // else if(pid1==0){
                        //     pid_t pid2=fork();
                        //     if(pid2<0){
                        //         printf("Unable to fork");
                        //     }
                        //     else if( !pid2 && execvp(S[0],S)<0){
                        //         perror("Error!Unable to run the command.\n");
                        //     }
                        //     else{
                        //         waitpid(pid2,&status,0);
                        //         if(!status){
                        //             printf("\n%s with pid %d exited\n",WORD,pid2);
                        //         }
                        //     }
                        // }
                        
                    }
                    cmd=strtok(NULL,";");          // says, that continue with the previous input strtok-ed for further searching
                }
            }
        }    
    }
}

