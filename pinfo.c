int str_to_int(char S[]){
    int num=0;
    for(int i=0;S[i];i++){
        num=num*10 + S[i] -'0';
    }
    return num;
}
char * rev_str(char* S,int len){
    char t;
    for(int i=0;i<len/2;i++){
        t=S[i];
        S[i]=S[len-1-i];
        S[len-1-i]=t;
    }
    return S;
}
char *  int_to_str(int n){
    char S[MAX];
    int i=0;
    while(n){
        S[i++]=n%10;
        n/=10;
    }
    S[i++]='\0';
    return rev_str(S,i);
}
int pinfo(char * cmd_tok){
    pid_t proc_id;
    char state;
    // char* word=strtok(cmd_tok," ");
    char * word=cmd_tok;
    proc_id=(word==NULL) ? getpid() : str_to_int(word);
    char path_status[MAX];
    char path_statm[MAX];
    char buf[MAX];
    char path_exec[MAX];
    char SOL[MAX];
    printf("pid -- %d\n",proc_id);
    char c;
    int len=0;
    sprintf(path_status, "/proc/%d/status", proc_id);
    FILE * fp=fopen(path_status,"r");
    if(fp){
        fgets(buf,256,fp);
        fgets(buf,256,fp);       // go ahead, by 2 lines.
        fgets(buf,256,fp);
        state=buf[8];
        sscanf(buf,"State:\t%c",&state);        // from buf, read in the format givn as arg2, and store the reqd %c in &state.
        if(state=='S'){
            strcpy(SOL,"Stopped");
        }
        else{
            strcpy(SOL,"Running");
        }
        printf("Process Status -- %s\n",SOL);
        fclose(fp);
    }
    else{
        printf("Error while opening system maintained file: status\n");
    }
    sprintf(path_statm,"/proc/%d/statm",proc_id);
    fp = fopen(path_statm, "r");
    if(fp) {
        c=fgetc(fp);
        while(c !=' '){
            buf[len++] = c;
            c=fgetc(fp);
        }
        fclose(fp);
        buf[len]='\0';
        printf("Memory -- %s\n", buf);
    }
    else{
        printf("Error while opening system maintained file: statm\n");
    }
    len=-1;
    sprintf(path_exec,"/proc/%d/exe",proc_id);
    len=readlink(path_exec,buf,MAX-1);
    if(len!=-1){
        buf[len] = '\0';
        strcpy(buf,TILDA(buf));
        printf("Executable Path -- %s\n", buf);
    }
    else {
        printf("Error while opening system maintained file: exe\n");
    }
}