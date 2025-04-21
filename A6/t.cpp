#include<bits/stdc++.h>
using namespace std;
void calculateInternalFrag(int originalBlockSize[],int blockSize[],int processSize[],int allocation[],int m,int n)
{
    int internalFrag[n];
    int totalInternalFrag=0;

    for(int i=0;i<n;i++)
    {
        if(allocation[i]!=-1)
        {
            int block=allocation[i];
            internalFrag[i]=blockSize[block];
            totalInternalFrag+=internalFrag[i];
        }
    }

    //display

    cout<<"\nProcess    Process size    Memory Block    Internal Frag"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<" "<<i+1<<"\t\t"<<processSize[i]<<"\t\t";
        if(allocation[i]!=-1)
        {
            cout<<allocation[i]+1<<"\t\t"<<internalFrag[i]<<endl;
        }
        else
        cout<<"Not Allocated!!"<<endl;
    }
}
void firstFit(int originalBlockSize[],int blockSize[],int processSize[],int m,int n){
    int allocation[n];
    for(int i=0;i<n;i++) allocation[i]=-1;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(processSize[i]<=blockSize[j])
            {
                allocation[i]=j;
                blockSize[j]-=processSize[i];
                break;
            }
        }
    }
cout<<"\nFirst Fit\n";
    calculateInternalFrag(originalBlockSize,blockSize,processSize,allocation,m,n);

}
 void bestFit(int originalBlockSize[],int blockSize[],int processSize[],int m,int n){
    int allocation[n];
    for(int i=0;i<n;i++) allocation[i]=-1;

    for(int i=0;i<n;i++)
    {
        int bestIdx=-1;
        for(int j=0;j<m;j++)
        {
            if(processSize[i]<=blockSize[j])
            {
                if(bestIdx==-1 || blockSize[bestIdx]>blockSize[j])
                {
                    bestIdx=j;
                }
            }
        }
        if(bestIdx!=-1)
        {
            allocation[i]=bestIdx;
            blockSize[bestIdx]-=processSize[i];
        }
    }
cout<<"\nBest Fit\n";
    calculateInternalFrag(originalBlockSize,blockSize,processSize,allocation,m,n);

}
void worstFit(int originalBlockSize[],int blockSize[],int processSize[],int m,int n){
    int allocation[n];
    for(int i=0;i<n;i++) allocation[i]=-1;

    for(int i=0;i<n;i++)
    {
        int worstIdx=-1;
        for(int j=0;j<m;j++)
        {
            if(processSize[i]<=blockSize[j])
            {
                if(worstIdx==-1 || blockSize[worstIdx]<blockSize[j])
                {
                    worstIdx=j;
                }
            }
        }
        if(worstIdx!=-1)
        {
            allocation[i]=worstIdx;
            blockSize[worstIdx]-=processSize[i];
        }
    }
cout<<"\nWorst Fit\n";
    calculateInternalFrag(originalBlockSize,blockSize,processSize,allocation,m,n);

}
void nextFit(int originalBlockSize[],int blockSize[],int processSize[],int m,int n){
    int allocation[n];
    for(int i=0;i<n;i++) allocation[i]=-1;
    int lastAllocated=0;
    for(int i=0;i<n;i++)
    {
        int j=lastAllocated, count=0;
        while(count<m)
        {
            if(processSize[i]<=blockSize[j])
            {
                allocation[i]=j;
                blockSize[j]-=processSize[i];
                break;
            }
            j=(j+1)%m;
            count++;
        }
    }
cout<<"\nNext Fit\n";
    calculateInternalFrag(originalBlockSize,blockSize,processSize,allocation,m,n);

}   

int main()
{
    int n, m;
    cout<<"Enter number of memory blocks :";
    cin>>m;
    int blockSize[m], originalBlockSize[m];
    cout<<"Enter block size :";
    for(int i=0;i<m;i++){
        cin>>blockSize[i];
        originalBlockSize[i]=blockSize[i];
    }

    cout<<"Enter number of processes :";
    cin>>n;
    int processSize[n];
    cout<<"Enter process size :";
    for(int i=0;i<n;i++) cin>>processSize[i];

firstFit(originalBlockSize, blockSize, processSize, m, n);

for(int i=0; i<m; i++) blockSize[i] = originalBlockSize[i];
bestFit(originalBlockSize, blockSize, processSize, m, n);

for(int i=0; i<m; i++) blockSize[i] = originalBlockSize[i];
worstFit(originalBlockSize, blockSize, processSize, m, n);

for(int i=0; i<m; i++) blockSize[i] = originalBlockSize[i];
nextFit(originalBlockSize, blockSize, processSize, m, n);



    return 0;
}