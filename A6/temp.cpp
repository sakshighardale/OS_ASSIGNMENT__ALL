#include<bits/stdc++.h>
using namespace std;

void calculateFramentation(int originalBlockSize[],int blockSize[],int m, int allocation[],int processSize[],int n)
{
    int internalFrag[n];
    int totalInternalFragment=0,externalFrag=0;
    for(int i=0;i<n;i++)
    {
        if(allocation[i]!=-1)
        {
            int blockIndex=allocation[i];
            internalFrag[i]=blockSize[blockIndex];
            totalInternalFragment+=internalFrag[i];
        }
        else{
            internalFrag[i]=-1; //not allocated;
        }
    }

    // //external fragmentation
    // for(int j=0;j<m;j++)
    // {
    //     if(blockSize[j]==originalBlockSize[j])
    //     externalFrag+=blockSize[j];
    // }

    //display internal frag per process
    cout << "\nProcess No.\tProcess Size\tBlock no.\tInternal Frag\n"; 
    for (int i = 0; i < n; i++)
    {
    cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
    
    if (allocation[i] != -1)
    {
    cout << allocation[i] + 1 << "\t\t" << internalFrag[i] << endl;
    }
    else
    {
    cout << "Not Allocated\t" << "-" << endl;
    }
    }
}

//first fit algo
void firstFit(int originalBlockSize[],int blockSize[], int m,int processSize[], int n)
{
    int allocation[n];
    for(int i=0;i<n;i++)
    {
        allocation[i]=-1;
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(blockSize[j]>=processSize[i])
            {
                allocation[i]=j;
                blockSize[j]-=processSize[i];
                break;
            }
        }
    }
    cout<<"\n--------First Fit Allocation---------"<<endl;
    calculateFramentation(originalBlockSize,blockSize,m,allocation,processSize,n);
}

//best fit algo
void bestFit(int originalBlockSize[],int blockSize[], int m,int processSize[], int n)
{
    int allocation[n];
    for(int i=0;i<n;i++) allocation[i]=-1;

    for(int i=0;i<n;i++)
    {
        int bestIdx=-1;
        for(int j=0;j<m;j++)
        {
            if(blockSize[j]>=processSize[i])
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

    cout<<"\n----------Best Fit----------"<<endl;
    calculateFramentation(originalBlockSize,blockSize,m,allocation,processSize,n);
}

void worstFit(int originalBlockSize[],int blockSize[], int m,int processSize[], int n)
{
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
cout<<"\n---------Worst Fit---------"<<endl;
calculateFramentation(originalBlockSize,blockSize,m,allocation,processSize,n);
}

void nextFit(int originalBlockSize[],int blockSize[], int m,int processSize[], int n)
{
    int allocation[n];
    int lastAllocated=0;
    for(int i=0;i<n;i++) allocation[i]=-1;

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

    cout<<"\n----Next Fit-----"<<endl;
    calculateFramentation(originalBlockSize,blockSize,m,allocation,processSize,n);
}
int main()
{
    int n, m;
    cout<<"Enter number of blocks :"; cin>>m;
    int blockSize[m], originalBlockSize[m];
    cout<<"Enter block size :";
    for(int i=0;i<m;i++)
    {
        cin>>blockSize[i];
        originalBlockSize[i]=blockSize[i];
    }
    cout<<"Enter number of proesses: ";
    cin>>n;
    int processSize[n];
    cout<<"Enter process size :";
    for(int i=0;i<n;i++)
    {
        cin>>processSize[i];
    }


    // firstFit(originalBlockSize,blockSize,m,processSize,n);
    
    // bestFit(originalBlockSize,blockSize,m,processSize,n);

    // worstFit(originalBlockSize,blockSize,m,processSize,n);
    nextFit(originalBlockSize,blockSize,m,processSize,n);

    return 0;
}