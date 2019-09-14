#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include <sys/utsname.h>
#include<signal.h>
#include "pwd.h"
// #include "pwd.c"
#define MAX 1001
#define SHELL_ADDR "/home/pstalwalkar7/2-1/OperatingSystems/Shell/1"

void cd(char dest[]){
    // printf("pwd::%s:\n",pwd());
    // printf("dir::::%c\n",dest[0]);
    // char * OLDPWD="";

    // char OLDPWD[MAX];
    // OLDPWD[0]='\0';
    // printf("OLDPWD:%s\n",OLDPWD);
    if(strcmp(dest,"")==0){
        int check=chdir(SHELL_ADDR);
        if(check){
            perror("Unable to change to home directory!\n");
        }
        else{
            // strcpy(OLDPWD,pwd());
            // OLDPWD=pwd();
        }
    }
    // else if(strcmp(dest,"-")==0){
    //     if(OLDPWD!=""){    // NOT BLANK
    //         int check=chdir(OLDPWD);
    //         if(check){
    //             perror("Error while changing to directory!\n");
    //         }
    //         else{
    //             printf("%s\n",OLDPWD);
    //             strcpy(OLDPWD,pwd());
    //             // OLDPWD=pwd();
    //         }
    //     }
    //     else{
    //         printf("shell: cd : OLDPWD not set.\n");
    //     }
    // }
    else if(dest[0]=='~'){
        char ds[MAX];
        strcpy(ds,SHELL_ADDR);
        int x=strlen(ds);
        int i;
        for(i=1;dest[i];i++){
            ds[x+i-1]=dest[i];
        }// concatenation effectively done.
        // printf("%s\n",ds);
        int check=chdir(ds);
        if(check){
            perror("Unable to change to given directory!\n");
        }
        else{
            // OLDPWD=pwd();
            // strcpy(OLDPWD,pwd());
        }
    }
    else{
        int check=chdir(dest);
        if(check){
            perror("Unable to change to directory!\n");
        }
        else{
            // strcpy(OLDPWD,pwd());
            // OLDPWD=pwd();
        }
    }
}