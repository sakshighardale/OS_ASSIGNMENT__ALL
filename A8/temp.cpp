#include <bits/stdc++.h>
using namespace std;
int disk_size=200;

void FCFS(vector<int>&arr,int head)
{
   int seek_count=0, distance;
   for(int currTrack:arr)
   {
    distance=abs(currTrack-head);
    seek_count+=distance;
    head=currTrack;
   }
   cout<<"Total number of seek operations :"<<seek_count<<endl;
   cout<<"Seek sequence : ";
   for(int track:arr) cout<<track <<" ";
   cout<<endl;
}


void calculatedDifference(vector<int>&request,int head, vector<pair<int,bool>>&diff)
{
    for(size_t i=0;i<request.size();i++)
    {
        diff[i].first=abs(head-request[i]);
    }
}

int findMin(vector<pair<int,bool>>&diff)
{
    int index=-1,minimum=1e9;
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


void shortesSeekTimeFirst(vector<int>&request, int head, int n)
{
    if(n==0) return;
    vector<pair<int,bool>> diff(n,{0,false});
    int seekCount=0;
    vector<int>seekSeq;
    for(int i=0;i<n;i++)
    {
        seekSeq.push_back(head);
        calculatedDifference(request,head,diff);
        int index=findMin(diff);
        diff[index].second=true;
        seekCount+=diff[index].first;
        head=request[index];
    }
    seekSeq.push_back(head);
    cout<<"Total number of seek operations :"<<seekCount<<endl;
   cout<<"Seek sequence : ";
   for(int track:request) cout<<track <<" ";
   cout<<endl;
}

void SCAN(vector<int>&arr,int head, string direction)
{
    int seekCnt=0, distance, currTrack;
    vector<int> left, right,seekseq;
    if(direction=="left")
    {
        left.push_back(0);
    }
    else{
        right.push_back(disk_size-1);
    }

    for(int track:arr)
    {
        if(track>head) right.push_back(track);
        else if(track<head) left.push_back(track);
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
                seekseq.push_back(currTrack);
                distance=abs(currTrack-head);
                seekCnt+=distance;
                head=currTrack;
            }
            direction="right";
        }
        else{
            for(int i=0;i<right.size();i++)
            {
                currTrack=right[i];
                seekseq.push_back(currTrack);
                distance=abs(currTrack-head);
                seekCnt+=distance;
                head=currTrack;
            }
            direction="left";
        }
    }
    cout<<"Total seek time is "<<seekCnt<<endl;
    cout<<"The seek sequence is ";
    for(int t:seekseq) cout<<t<<"  ";
    cout<<endl;
}
void CSCAN(vector<int>&arr,int head)
{
    int seekCount=0, distance;
    vector<int> left, right,seekSeq;
    left.push_back(0);
    right.push_back(disk_size-1);
    for (int track : arr) {
    if (track < head) left.push_back(track);
    else if (track > head) right.push_back(track);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for(int currTrack:right)
    {
        seekSeq.push_back(currTrack);
        distance=abs(currTrack-head);
        seekCount+=distance;
        head=currTrack;
    }

    //move to extreme left add that seek time too
    seekCount+=disk_size-1;
    head=0;

    for(int currTrack:left)
    {
        seekSeq.push_back(currTrack);
        distance=abs(currTrack-head);
        seekCount+=distance;
        head=currTrack;
    }

    cout<<"Total Seek time is"<<seekCount<<endl;
    cout<<"The seek sequence is ";
    for(int t:seekSeq) cout<<t<<"  ";
    cout<<endl;

}

int main()
{
int size;
cout<<"Enter the size :";
cin>>size;
vector<int> arr(size);
cout<<"Enter the processses :";
for(int i=0;i<size;i++)
cin>>arr[i];

int head=50;
string dir="left";

FCFS(arr,head);

shortesSeekTimeFirst(arr,head,size);

SCAN(arr,head,dir);

CSCAN(arr,head);
    return 0;
}