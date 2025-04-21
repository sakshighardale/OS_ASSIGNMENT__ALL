#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
// #include<sys/wait.h>  workd only in linux environment, uncomment this so to execute wait()

void copyFunc(char* src, char* des)
{
    pid_t pid=fork();
    if(pid<0)
    {
        printf("Unsuccessful..\n");
        exit(1);
    }
    else if(pid==0)//child process generated
    {
        printf("Child process generated with process is %d",getpid());
        execlp("./copyCommand","./copyCommand",src,des,NULL);
    }
    else if(pid>0) //return to parent process
    {
        wait(NULL);
    }
}

void grepFunc(char* searchStr, char* src)
{
    pid_t pid=fork();
    if(pid<0)
    {
        printf("Unsuccessful..\n");
        exit(1);
    }
    else if(pid==0)
    {
        printf("Child process generated with process is %d",getpid());
        execlp("./grepCommand","./grepCommand",searchStr,src,NULL);
    }
}

int main(int argc, char* argv[])
{
    if(argc<4)
    {
        printf("Invalid count of arguments!!");
        exit(1);
    }
    char* src=argv[1];
    char* des=argv[2];
    char* searchString=argv[3];
    while(1)
    {
        int c;
        printf("1.GrepCommand\t2.CopyCommand\t3.Exit\nEnter choice: ");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                grepFunc(searchString,src);
                break;
            case 2:
                copyFunc(src,des);
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Enter valid choice!!");
        }
    }

    return 0;
}