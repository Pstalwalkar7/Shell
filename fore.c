#define LIST_MAX 2000
char temp[MAX];
char* word;
pid_t pid;
void foreground(char *cmd){
    char *S[LIST_MAX];
    int status;
    word=strtok(cmd," ");
    int i=0;
    while(word!=NULL){
        S[i++]=word;
        word=strtok(NULL," ");
    }
    S[i++]="\0";
    pid=fork();
    // int status;
    if(pid<0){
        printf("Fork error!\n");
    }
    else if(pid>0){   // parent.
        waitpid(pid,&status,0);
    }
    else{    // child.
        execvp(S[0],S);
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
    // printf("FFF\n");
    char *S[LIST_MAX];
    int status;
    word=strtok(cmd," ");
    strcpy(temp,word);
    int i=0;
    while(word!=NULL){
        S[i++]=word;
        word=strtok(NULL," ");
    }
    S[i++]="\0";
    // pid_t pid;
    pid=fork();
    if(pid<0){
        printf("Fork error!\n");
    }
    else if(pid>0){
        ;
    }
    else if(!pid && execvp(S[0],S)<0){
        // printf("works");
        execvp(S[0],S);
        perror("Error!Unable to run the command.\n");
    }
}
