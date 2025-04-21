#include<iostream>
#include<vector>
using namespace std;

bool isSafe(vector<int> need, vector<int> currAvail, int m)
{
    for(int i=0;i<m;i++)
    {
        if(need[i]>currAvail[i])
        return false;
    }
    return true;
}
void banker(int n, int m, vector<vector<int>>& allocation, vector<vector<int>>&need, vector<vector<int>>&maxReq,bool& isSafeState,vector<int>&currAvail,vector<int>&processExe)
{
    vector<int> flag(n,0); //initially all unsafe
    int flag2=0;
    int cnt=0;
    while(flag2<n)
    {
        for(int i=0;i<n;i++)
        {
            if(flag[i]==0 && isSafe(need[i],currAvail,m))
            {
                for(int j=0;j<m;j++)
                {
                    currAvail[j]+=allocation[i][j];
                }
                flag[i]=1;
                processExe[flag2]=i;
                flag2++;
            }
            if(flag2==n)
            {
                isSafeState=true;
                cout<<"Safe State!!"<<endl;
                return;
            }
        }
        cnt++;
    }
    cout<<"Unsafe State!!";
    isSafeState=false;

}
int main()
{
    int n, m; //n->numOfProcesses  m->numOfResources
    cout<<"Enter number of processes ";
    cin>>n;
    cout<<"Enter number of resources: ";
    cin>>m;
    vector<vector<int>> allocation(n,vector<int>(m));
    vector<vector<int>> maxReq(n,vector<int>(m));
    vector<vector<int>> need(n,vector<int>(m));
    vector<int>processExe(n);
    vector<int> currAvail(m);
    cout<<"Enter Allocation matrix :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter for process P"<<i<<endl;
        for(int j=0;j<m;j++)
        {
            cin>>allocation[i][j];
        }
    }

    cout<<"Enter maximum requirement matrix :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter for process P"<<i<<endl;
        for(int j=0;j<m;j++)
        {
            cin>>maxReq[i][j];
        }
    }
    //calculating need matrix
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            need[i][j]=maxReq[i][j]-allocation[i][j];
        }
    }

    cout<<"Enter current available resources:"<<endl;
    for(int i=0;i<m;i++)
    {
            cin>>currAvail[i];
    }
    
    //display
    cout<<"Allocation Max Need"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<allocation[i][j]<<" ";
        }
        cout<<"\t";
        for(int j=0;j<m;j++)
        {
            cout<<maxReq[i][j]<<" ";
        }
        cout<<"\t";

        for(int j=0;j<m;j++)
        {
            cout<<need[i][j]<<" ";
        }

        cout<<endl;
    }
    bool isSafeState=false; 
    banker(n,m,allocation,need,maxReq,isSafeState,currAvail,processExe);
    if(isSafeState){
    for(int i=0;i<n-1;i++)
    {
        cout<<"P"<<processExe[i]<<"->";
    }
    cout<<"P"<<processExe[n-1]<<"\n";
    }
return 0;
}