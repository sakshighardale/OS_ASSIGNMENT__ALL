#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(int argc, char* argv[])
{
    //check if count of argument is as per requirement i.e. must be greater or equal 3
    if(argc<3)
    {
        printf("The count of argument must be atleast 3.");
        exit(1);
    }
    char* searchString=argv[1];
    FILE* rfile=fopen(argv[2],"r");
    if(rfile==NULL)
    {
        printf("Error in opening the source file!!");
        exit(1);
    }
    char line[1024];
    while(fgets(line,sizeof(line),rfile))
    {
        if(strstr(line,searchString)!=NULL)
        {
            printf("%s",line);
        }
    }
    fclose(rfile);

}