void Tilda_or_not(){
    char dir[MAX];
    if(getcwd(dir,sizeof(dir))==NULL){   // man doc: getcwd returns the abssolute directory path. Returns NULL if error.
        return 1;
    }
    else{
        // printf("%s\n",dir);
        int i;
        int match=1;
        char curr[]=".";
        char * path=realpath(curr,NULL);
        for(int k=strlen(path);k>=0;k--){
            if(path[k]=='/'){
                path[k]='\0';
                break;
            }
        }
        // printf("path::%s\n",path);
        if(path==NULL){    // unable to find curr , i.e "./main.c"
            printf("Error! Main file has been misplaced -- configuration disturbed !\n");
        }
        else{
            for(i=0;i<strlen(dir) && i<strlen(path);i++){
                if(dir[i]!=path[i]){
                    match=0;
                    break;
                }
            }
            if(i>=strlen(path) && match){    // match has definitely taken place completely...dir is equal or more than path of main
                char new[MAX];
                new[0]='~';
                for(int j=0;dir[i+j];j++){
                    new[j+1]=dir[i+j];
                }        
                printf("%s\n",new);
            }
            else{
                printf("%s\n",dir);
            }
        }
        return 0;
    }
}
