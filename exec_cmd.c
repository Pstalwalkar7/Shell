#include "exec_cmd.h"
// #include <readline/readline.h>
// #include <readline/history.h>
void exec_cmd(char * cmd){
    // printf("\n-------------------exec_CMD execution----------------\n");
    // printf("||||%s||||",cmd);
    char ** WORDS=calloc(MAX,sizeof(char));
    WORDS=Parse(cmd," ");
    char * det=WORDS[0];
    
    int valid_cd = !(strcmp(det,"cd") * strcmp(det,"cd\n"));
    int valid_echo = !(strcmp(det,"echo") * strcmp(det,"echo\n"));
    int valid_ls= !(strcmp("ls",det) * strcmp(det,"ls\n"));
    int valid_pwd= !(strcmp(det,"pwd") * strcmp(det,"pwd\n"));
    int valid_pinfo = !(strcmp(det,"pinfo") * strcmp(det,"pinfo\n"));
    int valid_quit = !(strcmp(det,"quit") * strcmp(det,"quit\n"));
    int valid_setenv = ! (strcmp(det,"setenv")*strcmp(det,"setenv\n"));
    int valid_unsetenv = !(strcmp(det,"unsetenv")*strcmp(det,"unsetenv\n"));
    int valid_kjob=!(strcmp(det,"kjob")*strcmp(det,"kjob\n"));
    int valid_jobs=!(strcmp(det,"jobs")*strcmp(det,"jobs\n"));
    int valid_fg=!(strcmp(det,"fg")*strcmp(det,"fg\n"));
    int valid_bg=!(strcmp(det,"bg")*strcmp(det,"bg\n"));
    int valid_overkill=!(strcmp(det,"overkill")*strcmp(det,"overkill\n"));

    if(valid_pwd){
        char * WorkingDir=malloc(MAX*sizeof(char));
        WorkingDir=pwd();
        if(!WorkingDir){
            printf("Error!\n");
        }
        else{
            printf("%s\n",WorkingDir);
        }
    }

    else if(valid_echo){
        char * DIR=malloc(sizeof(MAX));
        DIR=Savior_convert(WORDS,1,0);
        echo(DIR);
    }

    else if(valid_cd){
        char * To_dir=malloc(MAX*sizeof(char));
        if(WORDS[1]){            
            cd(WORDS[1]);
        }
        else{
            cd("");
        }
    }

    else if(valid_ls){
        char * DIR=malloc(sizeof(MAX)* sizeof(char));
        DIR=Savior_convert(WORDS,1,0);
        ls(DIR);
    }

    else if(valid_pinfo){
        pinfo(WORDS[1]);
    }
    else if(valid_setenv){
        if(WORDS[3] || !WORDS[1]){
            printf("Incorrect Number of parameters passed.\n");
        }
        else if(WORDS[1] && WORDS[2]){
            setenv(WORDS[1],WORDS[2],1);
        }
        else if(WORDS[1]){
            setenv(WORDS[1],"",0);
        }
    }
    else if(valid_unsetenv){
        if(! WORDS[1] || WORDS[2]){
            printf("Incorrect Number of parameters passed.\n");
        }
        else{
            unsetenv(WORDS[1]);
        }
    }
    else if(valid_kjob){
        if(!WORDS[2] || WORDS[3]){
            printf("Incorrect Number of parameters passed.\n");
        }
        else{
            if(atoi(WORDS[1])-1 >= Job_pos){
                printf("INVALID JOBID PASSED.\n");
            }    // ERROR HANDLING
            else{
                int te=kill(Jobs[atoi(WORDS[1])-1].PID,atoi(WORDS[2]));
                if(te){
                    printf("Signal can't be sent. Job id or Signal is invalid");
                }
                else{
                    printf("DONE\n");
                }
            }
        }
    }
    else if(valid_jobs){
        // printf("BOII\n");
        // maintain array of background processes, when you exit the background process, remove from array.
        if(WORDS[2]){
            printf("Error!\n");
        }
        else{
            pid_t proc_id;
            char path_status[MAX];
            char buf[MAX];
            char SOL[MAX];
            char state;
            int cnt=0;
            char * temp=malloc(sizeof(char)*1000);
            for(int x=0;x<Job_pos;x++){
                proc_id=Jobs[x].PID;
                sprintf(path_status, "/proc/%d/status", proc_id);
                FILE * fp=fopen(path_status,"r");
                if(fp){
                    cnt++;
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
                    // printf("||%c||",state);   // UNABLE TO READ. BLANK
                    printf("[%d]%s %s [%d]\n",cnt,SOL,Jobs[x].S,Jobs[x].PID);
                    fclose(fp);
                }
                else{    // Dont list it out.   As it is terminated.
                    ;
                }
            }
        }
    }
    else if(valid_fg){
        if(WORDS[2] || !WORDS[1]){
            printf("Incorrect number of parameters sent.\n");
        }
        else{
            if(atoi(WORDS[1])-1 >= Job_pos){
                printf("INVALID JOBID PASSED.\n");
            }    // ERROR HANDLING
            else{

            }
        }
    }
    else if(valid_bg){
        if(WORDS[2] || !WORDS[1]){
            printf("Incorrect number of parameters sent.\n");
        }
        else{
            if(atoi(WORDS[1])-1 >= Job_pos){
                printf("INVALID JOBID PASSED.\n");
            }    // ERROR HANDLING
            else{
                int te=kill(Jobs[atoi(WORDS[1])-1].PID,19);
                if(te){
                    printf("JOB ID IS INVALID.\n");
                }
            }
        } 
    }
    else if(valid_overkill){
        for(int x=0;x<Job_pos;x++){
            kill(Jobs[x].PID,9);
        }
    }
    else if(valid_quit){
        // printf("|Happend|");
        exit(0);
    }
    else{
        char * DIR=malloc(sizeof(MAX));
        DIR=Savior_convert(WORDS,0,0);
        for(int x=0;WORDS[x];x++)
        {
            if(!WORDS[x+1])
            {
                if(strcmp(WORDS[x],"&")==0)
                {
                    background(DIR);
                }
                else{
                    foreground(DIR);
                }
            }
        }
    }
}
