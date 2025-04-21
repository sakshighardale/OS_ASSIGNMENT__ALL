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
    int response_time = -1;
    int remaining_time;
};

void FCFS(vector<Process>& processes) {
    int n = processes.size();
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;
    processes[0].response_time = processes[0].arrival_time;

    for (int i = 1; i < n; i++) {
        processes[i].completion_time = max(processes[i - 1].completion_time, processes[i].arrival_time) + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i - 1].completion_time;
        totalTurnAroundTime += processes[i].turnaround_time;
        totalWaitingTime += processes[i].waiting_time;
    }

    cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.completion_time << "  | "
             << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
}

void SJF(vector<Process>& processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        if (a.arrival_time == b.arrival_time)
            return a.burst_time < b.burst_time;
        return a.arrival_time < b.arrival_time;
    });

    int totalWaitTime = 0, totalturnAroundTime = 0;
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = 0;
    processes[0].response_time = processes[0].arrival_time;

    for (int i = 1; i < n; i++) {
        processes[i].completion_time = max(processes[i - 1].completion_time, processes[i].arrival_time) + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i - 1].completion_time;
        totalturnAroundTime += processes[i].turnaround_time;
        totalWaitTime += processes[i].waiting_time;
    }

    cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.completion_time << "  | "
             << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWaitTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalturnAroundTime / n << endl;
}

void priorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    int totalWaitTime = 0, totalTurnaroundTime = 0;
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        if (a.arrival_time == b.arrival_time)
            return a.priority < b.priority;
        return a.arrival_time < b.arrival_time;
    });

    processes[0].completion_time = processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = 0;
    processes[0].response_time = processes[0].arrival_time;

    for (int i = 1; i < n; i++) {
        processes[i].completion_time = max(processes[i - 1].completion_time, processes[i].arrival_time) + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i - 1].completion_time;
        totalTurnaroundTime += processes[i].turnaround_time;
        totalWaitTime += processes[i].waiting_time;
    }

    cout << "\nProcess | AT | BT | P | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.priority << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWaitTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

void roundRobins(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<int> q;
    int currentTime = 0;
    vector<int> remaining(n);
    for (int i = 0; i < n; i++) {
        remaining[i] = processes[i].burst_time;
    }

    q.push(0);
    vector<bool> inQueue(n, false);
    inQueue[0] = true;

    while (!q.empty()) {
        int i = q.front(); q.pop();

        if (processes[i].response_time == -1) {
            processes[i].response_time = currentTime - processes[i].arrival_time;
        }

        int timeSlice = min(quantum, remaining[i]);
        remaining[i] -= timeSlice;
        currentTime += timeSlice;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= currentTime && remaining[j] > 0 && !inQueue[j]) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        if (remaining[i] > 0) {
            q.push(i);
        } else {
            processes[i].completion_time = currentTime;
            processes[i].turnaround_time = currentTime - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        }
    }

    cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
}

void SJF_Preemptive(vector<Process> processes) {
    int n = processes.size();
    int completed = 0, currentTime = 0;
    int totalWT = 0, totalTAT = 0;

    for (auto& p : processes)
        p.remaining_time = p.burst_time;

    while (completed < n) {
        int idx = -1, minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0 && processes[i].remaining_time < minBT) {
                minBT = processes[i].remaining_time;
                idx = i;
            }
        }

        if (idx != -1) {
            if (processes[idx].response_time == -1)
                processes[idx].response_time = currentTime - processes[idx].arrival_time;
            processes[idx].remaining_time--;
            currentTime++;

            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = currentTime;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                totalWT += processes[idx].waiting_time;
                totalTAT += processes[idx].turnaround_time;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;
}

void Priority_Preemptive(vector<Process> processes) {
    int n = processes.size();
    int completed = 0, currentTime = 0;
    int totalWT = 0, totalTAT = 0;

    for (auto& p : processes)
        p.remaining_time = p.burst_time;

    while (completed < n) {
        int idx = -1, minPr = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0 && processes[i].priority < minPr) {
                minPr = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            if (processes[idx].response_time == -1)
                processes[idx].response_time = currentTime - processes[idx].arrival_time;
            processes[idx].remaining_time--;
            currentTime++;

            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = currentTime;
                processes[idx].turnaround_time = currentTime - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                totalWT += processes[idx].waiting_time;
                totalTAT += processes[idx].turnaround_time;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    cout << "\nProcess | AT | BT | P | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.priority << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    int ch;
    cout << "1.FCFS  2.SJF  3.Priority  4.Round Robin  5.SJF Preemptive  6.Priority Preemptive\nEnter choice: ";
    cin >> ch;

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time & Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        if (ch == 3 || ch == 6)
        {
            cout << "Enter Priority: ";
            cin >> processes[i].priority;
        }
    }

    switch (ch) {
        case 1: FCFS(processes); break;
        case 2: SJF(processes); break;
        case 3: priorityScheduling(processes); break;
        case 4:
            int q;
            cout << "Enter quantum: ";
            cin >> q;
            roundRobins(processes, q);
            break;
        case 5: SJF_Preemptive(processes); break;
        case 6: Priority_Preemptive(processes); break;
        default: cout << "Invalid choice"; break;
    }

    return 0;
}
