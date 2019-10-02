void SETENV(char * var,char * val){     // default val to "" in case its not inputted.
    if(setenv(var,val,1)){
        printf("Error! Cannot set this environment variable.\n");
    }   // always change.    // check creation.
}

void UNSETENV(char * var){
    if(unsetenv(var)){
        printf("Error! Unable to unset an environment variable.\n");
    }
}