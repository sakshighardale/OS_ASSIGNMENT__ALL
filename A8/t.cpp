#include<bits/stdc++.h>
using namespace std;
int disk_size=200;

void FCFS(vector<int>&arr,int head, int n)
{
    int seekCount=0, distance, currTrack;
    for(int track:arr)
    {
        distance=abs(track-head);
        seekCount+=distance;
        head=track;
    }
    cout<<"The total seek time is "<<seekCount<<endl;
    cout<<"The seek sequence is ";
    for(int track:arr)
    {
        cout<<track<<" ";
    }
    cout<<endl;
}

void calculateDiff(vector<int>&arr, int head,vector<pair<int,bool>>&diff)
{
    for(size_t i=0;i<arr.size();i++)
    {
        diff[i].first=abs(arr[i]-head);
    }
}
int findMin(vector<pair<int,bool>>&diff)
{
    int index=-1, minimum=1e6;
    for(size_t i=0;i<diff.size();i++)
    {
        if(!diff[i].second && minimum>diff[i].first)
        {
            minimum=diff[i].first;
            index=i;
        }
    }
    return index;
}


void SSTF(vector<int>&arr, int head, int n)
{
    int seekCount=0, distance,currTrack;
    vector<pair<int,bool>>diff(n,{0,false});
    vector<int>seekSeq;
    for(int i=0;i<n;i++)
    {
        seekSeq.push_back(head);
        calculateDiff(arr,head,diff);
        int index=findMin(diff);
        diff[index].second=true;
        seekCount+=diff[index].first;
        head=arr[index];
    }
    seekSeq.push_back(head);

    cout<<"The total seek time is "<<seekCount<<endl;
    cout<<"The seek sequnce is ";
    for(int track :seekSeq) cout<<track<<"  ";
    cout<<endl;
}

void SCAN(vector<int>&arr, int head, string direction)
{
    int seekCount=0, distance,currTrack;
    vector<int>left,right,seekSeq;
    if(direction=="left") left.push_back(0);
    else if(direction=="right") right.push_back(disk_size-1);

    for(int track:arr)
    {
        if(track<head) left.push_back(track);
        else if(track>head) right.push_back(track);
    }
    sort(left.begin(),left.end());
    sort(right.begin(),right.end());
    
    int pass=2;
    while(pass-->0)
    {
        if(direction=="left")
        {
            for(int i=left.size()-1;i>=0;i--)
            {
                currTrack=left[i];
                seekSeq.push_back(currTrack);
                distance=abs(currTrack-head);
                seekCount+=distance;
                head=currTrack;
            }
            direction="right";
        }
        else{
            for(int i=0;i<right.size();i++)
            {
                currTrack=right[i];
                seekSeq.push_back(currTrack);
                distance=abs(currTrack-head);
                seekCount+=distance;
                head=currTrack;
            }
            direction="left";
        }
    }
    cout<<"The total seek count is "<<seekCount;
    cout<<"The seek sequence is ";
    for(int track:seekSeq) cout<<track<<"  ";
    cout<<endl;

}

void CSCAN(vector<int>arr, int head)
{
    int seekcount=0,distance,currTrack;
    vector<int> left,right,seekSeq;
    left.push_back(0);
    right.push_back(disk_size-1);
    for(int tr:arr)
    {
        if(tr>head) right.push_back(tr);
        else if(tr<head) left.push_back(tr);
    }
    sort(left.begin(),left.end());
    sort(right.begin(),right.end());

    for(int track:right)
    {
        seekSeq.push_back(track);
        distance=abs(track-head);
        seekcount+=distance;
        head=track;
    }

    seekcount+=disk_size-1;
    head=0;
    for(int track:left)
    {
        seekSeq.push_back(track);
        distance=abs(track-head);
        seekcount+=distance;
        head=track;
    }
    cout<<"The total seek count is "<<seekcount;
    cout<<"The seek sequence is ";
    for(int track:seekSeq) cout<<track<<"  ";
    cout<<endl;

}
int main()
{
    int n;
    cout<<"Enter number of processes :"; cin>>n;
    vector<int> arr(n);
    cout<<"Enter processes :";
    for(int i=0;i<n;i++) cin>>arr[i];
    int head=50;
    FCFS(arr,head,n);
    SSTF(arr,head,n);
    SCAN(arr,head,"left");
    SCAN(arr,head,"right");
    CSCAN(arr,head);
    return 0;
}