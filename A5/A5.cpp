#include <iostream>
#include <vector>
using namespace std;

bool isSafe(const vector<int>& need, const vector<int>& avail, int m)
{
    for(int i = 0; i < m; i++)
    {
        if(need[i] > avail[i])
            return false;
    }
    return true;
}

void banker(int n, int m, const vector<vector<int>>& allocation, const vector<vector<int>>& maxReq,
            vector<vector<int>>& need, vector<int>& currAvail, vector<int>&processExe,bool& isSafeState)
{
    vector<int> flag(n, 0);  // Initialize all processes as unsafe
    int flag2 = 0;
    int cnt = 0;

    while(flag2<n)
    {
        for(int i = 0; i < n; i++)
        {
            if(flag[i] == 0 && isSafe(need[i], currAvail, m))
            {
                for(int j = 0; j < m; j++)
                {
                    currAvail[j] += allocation[i][j];
                }
                flag[i] = 1;
                processExe[flag2]=i;
                flag2++;
            }
            if(flag2 == n)
            {
                cout << "Safe state" << endl;
                isSafeState=true;
                return;
            }
        }
        cnt++;
    }
    cout << "Unsafe state" << endl;
    isSafeState=false;
}

int main()
{
    int n, m;  // n -> number of processes, m -> number of resources
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));   // 2D vector for allocation matrix
    vector<vector<int>> maxReq(n, vector<int>(m));       // 2D vector for max requirement matrix
    vector<vector<int>> need(n, vector<int>(m));         // 2D vector for need matrix
    vector<int> currAvailable(m);                        // 1D vector for available resources
    vector<int> processExe(n);
    cout << "Enter the allocation matrix: " << endl;
    for(int i = 0; i < n; i++)
    {
        cout << "Enter for the process " << i + 1 << " : " << endl;
        for(int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the current available resources: ";
    for(int i = 0; i < m; i++)
    {
        cin >> currAvailable[i];
    }

    cout << "Enter the max requirement matrix: " << endl;
    for(int i = 0; i < n; i++)
    {
        cout << "Enter for the process " << i + 1 << " : " << endl;
        for(int j = 0; j < m; j++)
        {
            cin >> maxReq[i][j];
        }
    }

    // Calculate the need matrix
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            need[i][j] = maxReq[i][j] - allocation[i][j];
        }
    }
    //display need matrix
   
    cout<<"Allocation\tMax Required\tNeed"<<endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
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
    banker(n, m, allocation, maxReq, need, currAvailable,processExe,isSafeState);
    if(isSafeState==true)
    for(int i=0;i<n;i++)
    {
    cout<<"P"<<processExe[i]<<" ";
    }
    cout<<endl;
    return 0;
}
