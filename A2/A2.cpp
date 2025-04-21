#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

void FCFS(vector<Process>& processes) {
    int n = processes.size();
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Sort by Arrival Time
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

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.completion_time << "  | "
             << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << endl;
}

void SJF(vector<Process>& processes) {
    int n = processes.size();
    
    // Sort by Arrival Time, then by Burst Time
    sort(processes.begin(), processes.end(), [](Process p1, Process p2) {
        if (p1.arrival_time == p2.arrival_time)
            return p1.burst_time < p2.burst_time;
        return p1.arrival_time < p2.arrival_time;
    });

    int total_TAT = 0, total_WT = 0;
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        processes[i].completion_time = max(processes[i - 1].completion_time, processes[i].arrival_time) + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i - 1].completion_time;

        total_TAT += processes[i].turnaround_time;
        total_WT += processes[i].waiting_time;
    }

    cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.completion_time << "  | "
             << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }

    cout << "\nAverage Turnaround Time: " << (float)total_TAT / n << endl;
    cout << "Average Waiting Time: " << (float)total_WT / n << endl;
}

void PriorityScheduling(vector<Process>& processes) {
    int n = processes.size();

    // Sort by Arrival Time, then by Priority (Lower value = Higher priority)
    sort(processes.begin(), processes.end(), [](Process p1, Process p2) {
        if (p1.arrival_time == p2.arrival_time)
            return p1.priority < p2.priority;
        return p1.arrival_time < p2.arrival_time;
    });

    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        processes[i].completion_time = max(processes[i - 1].completion_time, processes[i].arrival_time) + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i - 1].completion_time;
    }

    cout << "\nProcess | AT | BT | P | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.priority << "  | "
             << p.completion_time << "  | " << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
}
// void display(vector<Process>& tasks) {
//     cout << "TN\tAT\tBT\tPoP\tCT\tTAT\tWT\tRT" << endl;
//     /*
// 	int id;
//     int arrival_time;
//     int burst_time;
//     int priority;
//     int completion_time;
//     int turnaround_time;
//     int waiting_time;
//     int response_time;*/
//     for (int i = 0; i < tasks.size(); i++) {
//         cout << "P"<<i << "\t"
//              << tasks[i].arrival_time << "\t"
//              << tasks[i].burst_time << "\t"
//              << tasks[i].priority << "\t"
//              << tasks[i].completion_time << "\t"
//              << tasks[i].turnaround_time << "\t"
//              << tasks[i].waiting_time << "\t"
//              << tasks[i].response_time << endl;
//     }
// }
void RoundRobin(vector<Process>& processes, int quantum) {
    queue<int> q;
    vector<int> remainingBurst(processes.size());
    for (int i = 0; i < processes.size(); i++)
        remainingBurst[i] = processes[i].burst_time;

    int currentTime = 0;
    q.push(0);
    vector<bool> inQueue(processes.size(), false);
    inQueue[0] = true;

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        if (processes[i].response_time == -1)
            processes[i].response_time = currentTime - processes[i].arrival_time;

        int execTime = min(quantum, remainingBurst[i]);
        remainingBurst[i] -= execTime;
        currentTime += execTime;

        for (int j = 0; j < processes.size(); j++) {
            if (processes[j].arrival_time <= currentTime && remainingBurst[j] > 0 && !inQueue[j]) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        if (remainingBurst[i] > 0)
            q.push(i);
        else {
            processes[i].completion_time = currentTime;
            processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        }
    }
    
    // display(processes);
    cout << "\nProcess | AT | BT | CT | TAT | WT | RT\n";
    for (const auto& p : processes) {
        cout << p.id << "      | " << p.arrival_time << "  | " << p.burst_time << "  | " << p.completion_time << "  | "
             << p.turnaround_time << "  | " << p.waiting_time << "  | " << p.response_time << endl;
    }
    // cout << "\nAverage Waiting Time: " << (float)totalWaitTime / n << endl;
    // cout << "Average Turnaround Time: " << (float)totalturnAroundTime / n << endl;

}

int main() {
    int choice;
    do {
        cout << "\n1) FCFS Scheduling\n2) SJF Scheduling\n3) Priority Scheduling\n4) Round Robin\n5) Exit\nEnter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            int n;
            cout << "Enter number of processes: ";
            cin >> n;
            vector<Process> processes(n);

            for (int i = 0; i < n; i++) {
                processes[i].id = i + 1;
                cout << "Enter Arrival Time & Burst Time for Process " << i + 1 << ": ";
                cin >> processes[i].arrival_time >> processes[i].burst_time;
                if (choice == 3) {
                    cout << "Enter Priority: ";
                    cin >> processes[i].priority;
                }
            }

            if (choice == 1) FCFS(processes);
            else if (choice == 2) SJF(processes);
            else if (choice == 3) PriorityScheduling(processes);
            else if (choice == 4) {
                int quantum;
                cout << "Enter Time Quantum: ";
                cin >> quantum;
                RoundRobin(processes, quantum);
            }
        }
    } while (choice != 5);

    return 0;
}
