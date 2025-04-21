#include <bits/stdc++.h>
using namespace std;

int disk_size = 200;

void FCFS(const vector<int>& arr, int head) {
    int seek_count = 0, distance, cur_track;
    for (int cur_track : arr) {
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    cout << "Total number of seek operations = " << seek_count << endl;
    cout << "Seek Sequence is" << endl;
    for (int track : arr) {
        cout << track << endl;
    }
}

void calculatedifference(const vector<int>& request, int head,vector<pair<int, bool>>& diff) {
    for (size_t i = 0; i < request.size(); i++) {
        diff[i].first = abs(head - request[i]);
    }
}

int findMIN(const vector<pair<int, bool>>& diff) {
    int index = -1, minimum = 1e9;
    for (size_t i = 0; i < diff.size(); i++) {
        if (!diff[i].second && minimum > diff[i].first) {
            minimum = diff[i].first;
            index = i;
        }
    }
    return index;
}

void shortestSeekTimeFirst(const vector<int>& request, int head, int n) {
    if (n == 0) return;
    vector<pair<int, bool>> diff(n, {0, false});
    int seekcount = 0;
    vector<int> seeksequence;

    for (int i = 0; i < n; i++) {
        seeksequence.push_back(head);
        calculatedifference(request, head, diff);
        int index = findMIN(diff);
        diff[index].second = true;
        seekcount += diff[index].first;
        head = request[index];
    }
    seeksequence.push_back(head);

    cout << "Total number of seek operations = " << seekcount << endl;
    cout << "Seek sequence is :" << endl;
    for (int track : seeksequence) {
        cout << track << endl;
    }
}

void SCAN(const vector<int>& arr, int head, string direction) {
    int seek_count = 0, distance, cur_track;
    vector<int> left, right, seek_sequence;

    if (direction == "left")
        left.push_back(0);
    else
        right.push_back(disk_size - 1);

    for (int track : arr) {
        if (track < head) left.push_back(track);
        else if (track > head) right.push_back(track);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int run = 2;
    while (run--) {
        if (direction == "left") {
            for (int i = left.size() - 1; i >= 0; i--) {
                cur_track = left[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "right";
        } else {
            for (int i = 0; i < right.size(); i++) {
                cur_track = right[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "left";
        }
    }

    cout << "Total number of seek operations = " << seek_count << endl;
    cout << "Seek Sequence is" << endl;
    for (int track : seek_sequence) {
        cout << track << endl;
    }
}

void CSCAN(const vector<int>& arr, int head) {
    int seek_count = 0, distance, cur_track;
    vector<int> left, right, seek_sequence;

    left.push_back(0);
    right.push_back(disk_size - 1);

    for (int track : arr) {
        if (track < head) left.push_back(track);
        else if (track > head) right.push_back(track);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int track : right) {
        seek_sequence.push_back(track);
        distance = abs(track - head);
        seek_count += distance;
        head = track;
    }

    // wrap around
    seek_count += (disk_size - 1);
    head = 0;

    for (int track : left) {
        seek_sequence.push_back(track);
        distance = abs(track - head);
        seek_count += distance;
        head = track;
    }

    cout << "Total number of seek operations = " << seek_count << endl;
    cout << "Seek Sequence is" << endl;
    for (int track : seek_sequence) {
        cout << track << endl;
    }
}

int main() {
    int size;
    cout << "Enter the Size: ";
    cin >> size;

    vector<int> arr(size);
    cout << "Enter the processes: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    int ch;
    int head = 50;
    string direction = "left";

    cout << "1. FCFS\t2. SSTF\t3. SCAN\t4. CSCAN\nEnter your choice: ";
    cin >> ch;

    switch (ch) {
        case 1:
            FCFS(arr, head);
            break;
        case 2:
            shortestSeekTimeFirst(arr, head, size);
            break;
        case 3:
            SCAN(arr, head, direction);
            break;
        case 4:
            cout << "Initial position of head: " << head << endl;
            CSCAN(arr, head);
            break;
        default:
            cout << "Enter Valid choice!!";
    }

    return 0;
}
