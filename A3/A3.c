#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
int main()
{
    pid_t pid;
    int fd[2];

        int ch;
        printf("1.Sort only\t2.Unique Only\t3.Both Sort and Unique\tEnter your choice :");
        scanf("%d",&ch);
        
    int filedes=open("file.txt",O_RDONLY);
    if(filedes<0)
    {
        perror("open");
        exit(1);
    }
    dup2(filedes,fileno(stdin));
    
    close(filedes);
        switch (ch)
        {
        case 1:
            execl("/usr/bin/sort","sort",NULL);
            perror("execl sort");
            exit(1);
            break;
        case 2:
            execl("/usr/bin/uniq","uniq","-c",NULL);
            perror("execl uniq");
            exit(1);
            break;
        case 3:
            pipe(fd);
            pid=fork();
            if(pid<0)
            {
                perror("fork");
                exit(1);
            }
            if(pid==0) //write into the file //child process //sort
            {
                dup2(fd[1],fileno(stdout));
                close(fd[0]);
                close(fd[1]);
                execl("/usr/bin/sort","sort",NULL);
            }
            else //read from the filec //parent process //unique
            {
                dup2(fd[0],fileno(stdin));
                close(fd[1]);
                close(fd[0]);
                execl("/usr/bin/uniq","uniq","-c",NULL);
            }
            break;
        default:
        printf("Enter Valid Choice!\n");
            break;
        }
    
    return 0;
}
