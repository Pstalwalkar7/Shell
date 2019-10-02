#include"fore.h"

// #define LIST_MAX 2000
char temp[MAX];
char* word;
pid_t pid;
void foreground(char *cmd)
{
    char *S[LIST_MAX];
    int status;
    word=strtok(cmd," ");
    strcpy(FORE.S,word);
    int i=0;
    while(word!=NULL){
        S[i++]=word;
        word=strtok(NULL," ");
    }
    S[i++]=NULL;
    
    pid=fork();
    FORE.PID=pid;
    if(pid<0)
    {
        printf("Fork error!\n");
    }
    else if(pid>0)
    { 
        // waitpid(pid,&status,0);
        // do{
        waitpid(pid,&status,WUNTRACED);
        // }while(!WIFSIGNALED(status) && !WIFSTOPPED(status));
        // wait (NULL);
        printf("watover  \n");
    }
    else
    {    // child.
        execvp(S[0],S);
        printf("ERROR! Unable to run the command!\n");
        exit(1);
    }
}
void sigchld_handler(int sig){
    int status;
    pid=waitpid(-1,&status,WNOHANG);
    if(pid>0){
        printf("\n%s with pid %d exited\n",temp,pid);
    }
}
void background(char * cmd){
    // pid cmd flag. 
    char *S[LIST_MAX];
    int status;
    word=strtok(cmd," ");
    strcpy(temp,word);
    int i=0;
    while(word!=NULL){
        S[i++]=word;
        word=strtok(NULL," ");
    }
    S[i++]=NULL;
    pid=fork();
    if(pid<0){
        printf("Fork error!\n");
    }
    else if(pid>0){
        // printf("exist");
        Jobs[Job_pos].PID=pid;
        strcpy(Jobs[Job_pos++].S,cmd);           
        ;
    }
    else if(!pid && execvp(S[0],S)<0){
        execvp(S[0],S);
        printf("Error!Unable to run the command.\n");
        exit(1);
    }
    else if(!pid){
        // printf("DONE\n");
        if(execvp(S[0],S)<0){
            execvp(S[0],S);
            printf("Error!Unable to run the command.\n");
            exit(1);
        }
        // else{
        //     Jobs[Job_pos].PID=pid;
        //     strcpy(Jobs[Job_pos++].S,cmd);           
        // }
    }
    // printf("///%d///",Job_pos);
}
