#include <dirent.h>
#define OP_MAX 10000
int unhidden(const struct dirent *entry){
    return (entry->d_name[0]!='.');
}
void ls(char cmd[]){
    int n;
    cmd=strtok(cmd,"|");
    // printf("\nCMD:|||||%s||||||\n",cmd);
    int flag[3]={0,0,0};
    struct dirent ** list;
    struct direct * parse;
    char * word=strtok(cmd," ");
    int mode=0;
    struct stat fileStat;
    char* month[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char timestr[20];
    struct tm *date_time;
    while(word!=NULL){
        if(strcmp(word,"-a")==0){
            mode=1;
        }
        else if(strcmp(word,"-l")==0){
            mode=2;
        }
        else if(strcmp(word,"-al")==0 || strcmp(word,"-la")==0){
            mode=3;
        }
        else if(mode==0 || mode==1){
            flag[mode]=1;
            if(mode==0){
                n=scandir(word,&list,unhidden,alphasort);   // poss contains the number of directories and files stored
            }
            else {
                printf("%s:\n",word);
                n=scandir(word,&list,NULL,alphasort);   // poss contains the number of directories and files stored    
            }
            if(n<0){
                printf("Error! Directory does not exist.\n");
            }
            else{
                for(int i=0;i<n;i++){
                    printf("%s   ",list[i]->d_name);
                    free(list[i]);
                }
            }
            printf("\n");
        }
        else if(mode==2 || mode==3){
            flag[mode]=1;
            printf("%s:\n",word);
            if (mode==2){
                n=scandir(word,&list,unhidden,alphasort);
            }
            else{
                n=scandir(word,&list,NULL,alphasort);
            }
            if(n<0){
                printf("Error! Directory does not exist.\n");
            }
            else{
                for(int i=0;i<n;i++){
                    if(stat(list[i]->d_name,&fileStat)<0){
                        printf("Error in reading file/directory:%s\n",list[i]->d_name);
                    }
                    else{
                        if(S_ISDIR(fileStat.st_mode)){
                            printf("d");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IRUSR){
                            printf("r");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IWUSR){
                            printf("w");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IXUSR){
                            printf("x");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IRGRP){
                            printf("r");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IWGRP){
                            printf("w");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IXGRP){
                            printf("x");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IROTH){
                            printf("r");
                        }
                        else{    
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IWOTH){
                            printf("w");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IXOTH){
                            printf("x");
                        }
                        else{    
                            printf("-");
                        }
                        printf("\t");
                        printf("%lu\t",fileStat.st_nlink);
                        struct passwd * user = getpwuid(fileStat.st_uid);
                        if (user){
                            printf("%s\t",user -> pw_name);
                        }
                        else{
                            printf("\t");
                        }
                        struct group * group = getgrgid(fileStat.st_gid);
                        if (group){
                            printf("%s\t",group -> gr_name);
                        }
                        else{
                            printf("\t");
                        }
                        if (lstat(list[i]->d_name,&fileStat)==0 && S_ISLNK(fileStat.st_mode)){  
                            printf("%ld\t",fileStat.st_size);
                        }
                        else{
                            printf("%ld\t",fileStat.st_size);
                        }
                        date_time = localtime(&fileStat.st_ctime);
                        printf("%s %d\t",month[date_time -> tm_mon],date_time -> tm_mday);
                        strftime(timestr, 100, "%H:%M\t", localtime(&fileStat.st_ctime));       // Need to check if access time ot modified time a_time,c_time,a_time
                        printf("%s    ",timestr);
                        printf("%s",list[i]->d_name);
                        printf("\n");
                    }
                }
            }
        }
        word=strtok(NULL," ");
    }
    if(word==NULL && flag[mode]==0){
        if(mode==0 || mode==1){
            if(mode==0){
                n=scandir(".",&list,unhidden,alphasort);   // poss contains the number of directories and files stored
            }
            else{
                n=scandir(".",&list,NULL,alphasort);   // poss contains the number of directories and files stored
            }
            if(n<0){
                printf("Strange error occured!\n");
            }
            else{
                for(int i=0;i<n;i++){
                    printf("%s   ",list[i]->d_name);
                    free(list[i]);
                }
            }
            printf("\n");
        }
        else{
            // printf("%s:\n",word);
            if (mode==2){
                n=scandir(".",&list,unhidden,alphasort);
            }
            else{
                n=scandir(".",&list,NULL,alphasort);
            }
            if(n<0){
                printf("Error! Directory does not exist.\n");
            }
            else{
                for(int i=0;i<n;i++){
                    if(stat(list[i]->d_name,&fileStat)<0){
                        printf("Error in reading file/directory.\n");
                    }
                    else{
                        if(S_ISDIR(fileStat.st_mode)){
                            printf("d");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IRUSR){
                            printf("r");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IWUSR){
                            printf("w");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IXUSR){
                            printf("x");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IRGRP){
                            printf("r");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IWGRP){
                            printf("w");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IXGRP){
                            printf("x");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IROTH){
                            printf("r");
                        }
                        else{    
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IWOTH){
                            printf("w");
                        }
                        else{
                            printf("-");
                        }
                        if (fileStat.st_mode & S_IXOTH){
                            printf("x");
                        }
                        else{    
                            printf("-");
                        }
                        printf("\t");
                        printf("%lu\t",fileStat.st_nlink);
                        struct passwd * user = getpwuid(fileStat.st_uid);
                        if (user){
                            printf("%s\t",user -> pw_name);
                        }
                        else{
                            printf("\t");
                        }
                        struct group * group = getgrgid(fileStat.st_gid);
                        if (group){
                            printf("%s\t",group -> gr_name);
                        }
                        else{
                            printf("\t");
                        }
                        if (lstat(list[i]->d_name,&fileStat)==0 && S_ISLNK(fileStat.st_mode)){
                            printf("%ld\t",fileStat.st_size);
                        }
                        else{
                            printf("%ld\t",fileStat.st_size);
                        }
                        date_time = localtime(&fileStat.st_ctime);
                        printf("%s %d\t",month[date_time -> tm_mon],date_time -> tm_mday);
                        strftime(timestr, 100, "%H:%M\t", localtime(&fileStat.st_ctime));       // Need to check if access time ot modified time a_time,c_time,a_time
                        printf("%s    ",timestr);
                        printf("%s",list[i]->d_name);
                        printf("\n");
                    }
                }
            }
        }
    }
}