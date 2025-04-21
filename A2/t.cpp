#include<bits/stdc++.h>
using namespace std;
struct Process{
    int id;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time=-1;
    int burst_time;
    int priority;
};
void FCFS(vector<Process>&processes)
{
    int totalTA=0, totalWT=0;
    int n=processes.size();
    sort(processes.begin(),processes.end(),[] (Process a,Process b){
        return a.arrival_time<b.arrival_time;
    });

    processes[0].completion_time=processes[0].arrival_time+processes[0].burst_time;
    processes[0].turnaround_time=processes[0].completion_time-processes[0].arrival_time;
    processes[0].waiting_time=processes[0].turnaround_time-processes[0].burst_time;
    processes[0].response_time=processes[0].arrival_time;

    for(int i=1;i<n;i++)
    {
    processes[i].completion_time=max(processes[i-1].completion_time,processes[i].arrival_time)+processes[i].burst_time;
    processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
    processes[i].waiting_time=processes[i].turnaround_time-processes[i].burst_time;
    processes[i].response_time=processes[i-1].completion_time;  
    totalTA+=processes[i].turnaround_time;
    totalWT+=processes[i].waiting_time;
    }
    cout << "\nProcess | AT | BT | P | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.priority << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWT/ n << endl;
    cout << "Average Turnaround Time: " << (float)totalTA / n << endl;
}

void SJF(vector<Process>&processes)
{
    int totalTA=0, totalWT=0;
    int n=processes.size();
    sort(processes.begin(),processes.end(),[] (Process a,Process b){
        if(a.arrival_time==b.arrival_time)
            return a.burst_time<b.burst_time;
        return a.arrival_time<b.arrival_time;
    });

    processes[0].completion_time=processes[0].arrival_time+processes[0].burst_time;
    processes[0].turnaround_time=processes[0].completion_time-processes[0].arrival_time;
    processes[0].waiting_time=processes[0].turnaround_time-processes[0].burst_time;
    processes[0].response_time=processes[0].arrival_time;

    for(int i=1;i<n;i++)
    {
    processes[i].completion_time=max(processes[i-1].completion_time,processes[i].arrival_time)+processes[i].burst_time;
    processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
    processes[i].waiting_time=processes[i].turnaround_time-processes[i].burst_time;
    processes[i].response_time=processes[i-1].completion_time;  
    totalTA+=processes[i].turnaround_time;
    totalWT+=processes[i].waiting_time;
    }
    cout << "\nProcess | AT | BT | P | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.priority << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTA / n << endl;
}
void PQ(vector<Process>&processes)
{
    int totalTA=0, totalWT=0;
    int n=processes.size();
    sort(processes.begin(),processes.end(),[] (Process a,Process b){
        if(a.arrival_time==b.arrival_time)
            return a.priority<b.priority;
        return a.arrival_time<b.arrival_time;
    });

    processes[0].completion_time=processes[0].arrival_time+processes[0].burst_time;
    processes[0].turnaround_time=processes[0].completion_time-processes[0].arrival_time;
    processes[0].waiting_time=processes[0].turnaround_time-processes[0].burst_time;
    processes[0].response_time=processes[0].arrival_time;

    for(int i=1;i<n;i++)
    {
    processes[i].completion_time=max(processes[i-1].completion_time,processes[i].arrival_time)+processes[i].burst_time;
    processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
    processes[i].waiting_time=processes[i].turnaround_time-processes[i].burst_time;
    processes[i].response_time=processes[i-1].completion_time;  
    totalTA+=processes[i].turnaround_time;
    totalWT+=processes[i].waiting_time;
    }
    cout << "\nProcess | AT | BT | P | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.priority << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTA / n << endl;
}
void RR(vector<Process>&processes,int quantum)
{
    queue<int> q;
    int totalWT=0,totalTA=0;
    int n=processes.size();
    vector<int> remainingBT(n);
    for(int i=0;i<n;i++) remainingBT[i]=processes[i].burst_time;
    int currentTime=0;
    vector<bool> inqueue(n,false);

    q.push(0);
    inqueue[0]=true;
    while(!q.empty()){
        int i=q.front();
        q.pop();

        if(processes[i].response_time==-1)
        {
            processes[i].response_time=currentTime-processes[i].arrival_time;
        }

        int exec=min(quantum,remainingBT[i]);
        remainingBT[i]-=exec;
        currentTime+=exec;
        for(int j=0;j<n;j++)
        {
            if(processes[j].arrival_time<=currentTime && remainingBT[j]>0 && !inqueue[j])
            {
                q.push(j);
                inqueue[j]=true;
            }
        }
        if(remainingBT[i]>0)
            q.push(i);
        else{
            processes[i].completion_time=currentTime;
            processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
            processes[i].waiting_time=processes[i].turnaround_time-processes[i].burst_time;
            totalTA+=processes[i].turnaround_time;
            totalWT+=processes[i].waiting_time;
        }

    }


    cout << "\nProcess | AT | BT | P | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.priority << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTA / n << endl;
}
int main()
{
    int n;
    cout<<"Enter number of processes :";
    cin>>n;
    vector<Process> processes(n);
    cout<<"Enter arrival Time & Burst Time :";
    for(int i=0;i<n;i++)
    {
        processes[i].id=i;
        cin>>processes[i].arrival_time>>processes[i].burst_time;
    }
    FCFS(processes);
    SJF(processes);
    PQ(processes);
    RR(processes,2);
    return 0;
}