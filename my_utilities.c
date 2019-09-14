char new[MAX];
// void handle_sigchld(int sig){
//     fprintf(STDERR_FILENO,"%d\n",sig);
// }
int next_sp(char S[],int pos){   // returns position of next space. if -1 then no next space present. else, S[ret_val] is ' '. 
    for(int i=pos;S[i];i++){
        if(S[i]==' '){
            return i;
        }
    }
    return -1;    
}
char* TILDA(char dir[]){
    // char dir[MAX];
    // if(getcwd(dir,sizeof(dir))==NULL){   // man doc: getcwd returns the abssolute directory path. Returns NULL if error.
    //     printf("Error. Current directory cannot be accessed.\n");
    // }
    // else{
        // printf("%s\n",dir);
        int i;
        int match=1;
        char path[]=SHELL_ADDR;               
        for(i=0;i<strlen(dir) && i<strlen(path);i++){
            if(dir[i]!=path[i]){
                match=0;
                break;
            }
        }
        if(i>=strlen(path) && match){    // match has definitely taken place completely...dir is equal or more than path of main
            // printf("\nIN\n");
            new[0]='~';
            int j;
            for(j=0;dir[i+j];j++){
                new[j+1]=dir[i+j];
            }    
            new[j+1]='\0';         // KEY LINE .
            // printf("%s>",new);
            return new;
        }
        else{
            // printf("%s>",dir);
            return dir;
        }
        // }
    // }
}

char * rem_leading_spaces(char * S){
    int len=strlen(S);
    for(int i=0;i<len;i++){
        if(S[i]!=' '){
            return S+i;
        }
    }
    return S;
}
int str_match(char * S,char * Command){
    int len=strlen(S);
    int Com_len=strlen(Command);
    int i=0;
    while(i<len && S[i]==' '){
        i++;
    }
    int start=i;
    i=len-1;
    while(i>=0 && (S[i]==' ' || S[i]=='\n')){
        i--;
    }
    int end=i;
    int k=0;
    if(end-start+1==Com_len){
        for(int j=start;j<=end;j++){
            if (S[j]!=Command[k++]){
                return 0;
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}