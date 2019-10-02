#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include <sys/utsname.h>
#include<signal.h>
#include "pwd.h"
#define MAX 1001
#define SHELL_ADDR "/home/pstalwalkar7/2-1/OperatingSystems/Shell/1"

void cd(char dest[]){
    if(strcmp(dest,"")==0){
        int check=chdir(SHELL_ADDR);
        if(check){
            perror("Unable to change to home directory!\n");
        }
    }
    else if(dest[0]=='~'){
        char ds[MAX];
        strcpy(ds,SHELL_ADDR);
        int x=strlen(ds);
        int i;
        for(i=1;dest[i];i++){
            ds[x+i-1]=dest[i];
        }// concatenation effectively done.
        int check=chdir(ds);
        if(check){
            perror("Unable to change to given directory!\n");
        }
    }
    else{
        int check=chdir(dest);
        if(check){
            perror("Unable to change to directory!\n");
        }
    }
}