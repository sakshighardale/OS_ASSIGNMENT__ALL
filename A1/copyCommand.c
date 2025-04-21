#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(int argc, char* argv[])
{
    if(argc<3)
    {
        printf("Invalid argument count!!");
        exit(1);
    }
    FILE* rfile=fopen(argv[1],"r");
    FILE* wfile=fopen(argv[2],"w");
    if(rfile==NULL)
    {
        printf("Error in openening the file!!");
        exit(1);
    }
    char dataToBeWritten[30];
    while(fgets(dataToBeWritten,sizeof(dataToBeWritten),rfile))
    {
        fputs(dataToBeWritten,wfile);
    }
    fclose(rfile);
    fclose(wfile);
}