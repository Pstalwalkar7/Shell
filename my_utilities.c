char new[MAX];
int next_sp(char S[],int pos){   // returns position of next space. if -1 then no next space present. else, S[ret_val] is ' '. 
    for(int i=pos;S[i];i++){
        if(S[i]==' '){
            return i;
        }
    }
    return -1;    
}
char * Savior_convert(char ** WORDS,int start_offset,int end_offset){
    // char DIR[MAX];
    char * DIR=calloc(MAX,sizeof(char));
    DIR[0]='\0';
    for(int i=start_offset;WORDS[i+end_offset];i++)
    {         // max kept to avoid seg fault in case of mad ip
        strcat(DIR," ");
        strcat(DIR,WORDS[i]);
    }
    return DIR;
}
char ** Parse(char * cmd,char* delim){
    char ** WORDS=malloc(MAX*sizeof(char*));
    int pos=0;
    char * word;
    word=strtok(cmd,delim);
    // write(restore_out,word,strlen(word));
    while(word){
        WORDS[pos++]=word;
        word=strtok(NULL,delim);
    }
    WORDS[pos]=NULL;
    // printf("\n\n%s ::",delim);
    // for(int i=0;WORDS[i];i++){
    //     printf("<%s>",WORDS[i]);
    // }
    // write(restore_out,"Jo",2);
    
    // write()
    return WORDS;
}
char* TILDA(char dir[]){
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
        new[0]='~';
        int j;
        for(j=0;dir[i+j];j++){
            new[j+1]=dir[i+j];
        }    
        new[j+1]='\0';         // KEY LINE .
        return new;
    }
    else{
        return dir;
    }
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