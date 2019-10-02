char dir[MAX];
char* pwd(){
    if(getcwd(dir,sizeof(dir))==NULL){   // man doc: getcwd returns the abssolute directory path. Returns NULL if error.
        return "\0";
    }
    else{
        return dir;
    }
}
