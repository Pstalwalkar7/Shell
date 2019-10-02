#include "redir.h" 
int ChangeOP(char * file){
    int op=open(file,O_WRONLY| O_TRUNC |O_CREAT,0644);
    if(op<0){
        printf("ERROR! Nearly Impossible error. Not able to write or even create the given file name.\n");
        return -1;
    }
    else{
        dup2(op,1);
        close(op);
        return 1;
    }
}
int ChangeIP(char *file){
    int ip=open(file,O_RDONLY);
    if(ip<0){
        printf("ERROR! File Does not exist!\n");
        return -1;
    }
    else{
        dup2(ip,0);     // essentially does is makes dup2 0 not otherwise.
        close(ip);
        return 1;
    }
}
int EnableAppend(char * file){      // for >>and <<(?)
    printf("%s mouse \n",file);
    int op=open(file,O_CREAT|O_APPEND|O_WRONLY,0644);
    if(op<0)
    {
        printf("ERROR! Nearly Impossible error. Not able to write or even create the given file name.\n");
        return -1;
    }
    else
    {
        dup2(op,1);
        close(op);
        return 1;
    }
}
char ** redirIO(char ** WORDS){
    char ** res_args=malloc(MAX*sizeof(char*));
    int res_args_cnt=0;
    int redir=0;
    for(int i=0;WORDS[i];i++)
    {
        if(strcmp(WORDS[i],">")==0)
        {
            redir=1;
            if(WORDS[i+1]){
                ChangeOP(WORDS[i+1]);
            }
            else{
                printf("ERROR! Invalid '>' present.");
            }
        }
        else if(strcmp(WORDS[i],"<")==0)
        {
            redir=1;
            if(WORDS[i+1]){
                ChangeIP(WORDS[i+1]);
            }
            else{
                printf("ERROR! Invalid '<' present.");
            }
        }
        else if(strcmp(WORDS[i],">>")==0)
        {
            redir=1;
            if(WORDS[i+1])
            {
                printf("Callign function overh ere \n");
                EnableAppend(WORDS[i+1]);
            }
            else
            {
                printf("ERROR! Invalid '>>' present");
            }
        }
        else if(!redir)
        {
            res_args[res_args_cnt++]=WORDS[i];
        }
    }
    res_args[res_args_cnt] = NULL;
    return res_args;
}
