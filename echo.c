void echo(char cmd[]){
    char Print[MAX];
    int pos=0;
    int quotes[2]={0,0};    // DOES not contain actual number of "" or '' . Used for even odd. odd within even cases also. CONTAINS " & ' outside each of other.
    // cmd=rem_leading_spaces(cmd+4);    // DONE IN SHELL
    // printf("%s",cmd);
    int new_line=0;
    for(int i=0;cmd[i];i++){
        if(cmd[i]==' ' && quotes[0]%2==0 && quotes[1]%2==0){
            Print[pos++]=cmd[i];
            cmd=rem_leading_spaces(cmd+i);
            i=-1;   // i++ will make it 0 next step.
        }
        else if(cmd[i]=='\''){
            if(quotes[1]%2==0){     // if not within the " " , then 
                quotes[0]++;            //dont print
            }
            else{
                Print[pos++]=cmd[i];
            }
        }
        else if(cmd[i]=='"'){
            if(quotes[0]%2==0){
                quotes[1]++;
            }
            else{
                Print[pos++]=cmd[i];
            }
        }
        else if(cmd[i]=='\n'){
            new_line=1;
            Print[pos++]='\n';
        }
        else{
            Print[pos++]=cmd[i];
        }
    }
    Print[pos++]='\0';
    if(quotes[0]%2 || quotes[1]%2){
        printf("Multiline echo not supported yet. Missing ' or \".\n");
    }
    else{
        if(new_line){
            printf("%s",Print);
        }
        else{
            printf("%s\n",Print);
        }
    }
}