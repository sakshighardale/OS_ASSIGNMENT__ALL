#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct Process{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time=-1;
};

void FCFS(vector<Process>& processes)
{
    int n=processes.size();
    int totalWaitingTime=0, totalTurnAroundTime=0;
    //sort by arrival time
    sort(processes.begin(),processes.end(),[](Process a, Process b)
    {
       return a.arrival_time<b.arrival_time;
    });

    processes[0].completion_time=processes[0].arrival_time+processes[0].burst_time;
    processes[0].waiting_time=0;
    processes[0].turnaround_time=processes[0].burst_time;
    processes[0].response_time=processes[0].arrival_time;
    
    for(int i=1;i<n;i++)
    {
       
    processes[i].completion_time=max(processes[i-1].completion_time,processes[i].arrival_time)+processes[i].burst_time;
    processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
    processes[i].waiting_time=processes[i].turnaround_time-processes[i].burst_time;
    processes[i].response_time=processes[i-1].completion_time; 

    totalTurnAroundTime+=processes[i].turnaround_time;
    totalWaitingTime+=processes[i].waiting_time;
    }
 cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.completion_time << "  | "
             << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
}

void SJF(vector<Process>&processes)
{
    int n=processes.size();

    //sort by Arrival time and then by burst time
    sort(processes.begin(),processes.end(),[](Process a,Process b)
    {
        if(a.arrival_time==b.arrival_time)
            return a.burst_time<b.burst_time;
        return a.arrival_time<b.arrival_time;
    });

    int totalWaitTime=0, totalturnAroundTime=0;
    processes[0].completion_time=processes[0].arrival_time+processes[0].burst_time;
    processes[0].turnaround_time=processes[0].completion_time-processes[0].arrival_time;
    processes[0].waiting_time=0;
    processes[0].response_time=processes[0].arrival_time;

    for(int i=1;i<n;i++)
    {
        processes[i].completion_time=max(processes[i-1].completion_time,processes[i].arrival_time)+processes[i].burst_time;
        processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
        processes[i].waiting_time=processes[i].turnaround_time-processes[i].burst_time;
        processes[i].response_time=processes[i-1].completion_time;
        totalturnAroundTime+=processes[i].turnaround_time;
        totalWaitTime+=processes[i].waiting_time;
    }
    cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.completion_time << "  | "
             << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWaitTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalturnAroundTime / n << endl;

}
void priorityScheduling(vector<Process>& processes)
{
    int n=processes.size();
    int totalWaitTime=0, totalTurnaroundtime=0;

    //sort by arrival and then by priority
    sort(processes.begin(),processes.end(),[](Process a, Process b){
        if(a.arrival_time==b.arrival_time)
        return a.priority<b.priority;
        return a.arrival_time<b.arrival_time;
    });

    processes[0].completion_time=processes[0].burst_time;
    processes[0].turnaround_time=processes[0].completion_time-processes[0].arrival_time;
    processes[0].waiting_time=0;
    processes[0].response_time=processes[0].arrival_time;
    for(int i=1;i<n;i++)
    {
    processes[i].completion_time=max(processes[i-1].completion_time,processes[i].arrival_time)+processes[i].burst_time;
    processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
    processes[i].waiting_time=processes[i].turnaround_time-processes[i].burst_time;
    processes[i].response_time=processes[i-1].completion_time;
    totalTurnaroundtime+=processes[i].turnaround_time;
    totalWaitTime+=processes[i].waiting_time;
    }
    cout << "\nProcess | AT | BT | P | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.priority << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWaitTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundtime / n << endl;
}
void roundRobins(vector<Process>& processes, int quantum)
{
    queue<int> q;
    int currentTime=0;
    int n=processes.size();
    vector<int>remainingBurstTime(n);
    for(int i=0;i<n;i++)
    {
        remainingBurstTime[i]=processes[i].burst_time;
    }
    q.push(0);
    vector<bool> inqueue(n,false);
    inqueue[0]=true;
    while(!q.empty())
    {
        int i=q.front();
        q.pop();

        if(processes[i].response_time==-1)
        {
            processes[i].response_time=currentTime-processes[i].arrival_time;
        }

        int exec=min(quantum,remainingBurstTime[i]);
        remainingBurstTime[i]-=exec;
        currentTime+=exec;

        for(int j=0;j<n;j++)
        {
            if(processes[j].arrival_time<=currentTime && remainingBurstTime[j]>0 && !inqueue[j])
            {
                q.push(j);
                inqueue[j]=true;
            }
        }

        if(remainingBurstTime[i]>0)
        {
            q.push(i);
        }
        else
        {
            processes[i].completion_time=currentTime;
            processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
            processes[i].waiting_time=processes[i].turnaround_time-processes[i].burst_time;
        }
    }
    cout<<"\nProcess    AT    BT      CT      TAT    WT   RT"<<endl;
    for(const auto&p:processes)
    {
    cout<<p.id<<"  |   "<<p.arrival_time<<"    |   "<<p.burst_time<<"  |   "<<p.completion_time<<" |   "<<p.turnaround_time<<" |   "<<p.waiting_time<<"    |   "<<p.response_time<<endl;
    }

}
int main()  {
            int n;
            cout << "Enter number of processes: ";
            cin >> n;
            vector<Process> processes(n);
            int ch;
            cout<<"1.FCFS\t2.SJF\t3.Priority\t4.Round Robin Enter choice: ";
            cin>>ch;
            for (int i = 0; i < n; i++) {
                processes[i].id = i + 1;
                cout << "Enter Arrival Time & Burst Time for Process " << i + 1 << ": ";
                cin >> processes[i].arrival_time >> processes[i].burst_time;
                if(ch==3)
                {
                    cout << "Enter Priority: ";
                    cin >> processes[i].priority;
                }
                }
            
            switch(ch)
            {
                case 1:
                    FCFS(processes);
                break;
                case 2:
                    SJF(processes);
                break;
                case 3:
                    priorityScheduling(processes);
                break;
                case 4:
                    int quantum;
                    cout<<"Enter qunatum : ";
                    cin>>quantum;
                    roundRobins(processes,quantum);
                break;
                default :
                cout<<"Enter valid choice!";
                break;
            }
            
}
