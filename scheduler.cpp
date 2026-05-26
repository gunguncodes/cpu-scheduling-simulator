#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, arrival, burst;
    int remaining;
};

struct GanttBlock {
    int pid, start, end;
};

struct Result {
    int pid, arrival, burst;
    int completion, turnaround, waiting;
};

void printJSON(const string& algo, const vector<GanttBlock>& gantt, const vector<Result>& results) {
    cout << "{\n";
    cout << "  \"algorithm\": \"" << algo << "\",\n";

    cout << "  \"gantt\": [";
    for (int i = 0; i < (int)gantt.size(); i++) {
        if (i) cout << ", ";
        cout << "{\"pid\": " << gantt[i].pid
             << ", \"start\": " << gantt[i].start
             << ", \"end\": " << gantt[i].end << "}";
    }
    cout << "],\n";

    cout << "  \"results\": [\n";
    for (int i = 0; i < (int)results.size(); i++) {
        if (i) cout << ",\n";
        cout << "    {\"pid\": " << results[i].pid
             << ", \"arrival\": " << results[i].arrival
             << ", \"burst\": " << results[i].burst
             << ", \"completion\": " << results[i].completion
             << ", \"turnaround\": " << results[i].turnaround
             << ", \"waiting\": " << results[i].waiting << "}";
    }
    cout << "\n  ]\n}\n";
}

// FCFS
void fcfs(vector<Process> procs) {
    sort(procs.begin(), procs.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    vector<GanttBlock> gantt;
    vector<Result> results;
    int time = 0;

    for (auto& p : procs) {
        if (time < p.arrival) time = p.arrival;
        gantt.push_back({p.id, time, time + p.burst});
        time += p.burst;
        int ct = time, tat = ct - p.arrival, wt = tat - p.burst;
        results.push_back({p.id, p.arrival, p.burst, ct, tat, wt});
    }

    printJSON("FCFS", gantt, results);
}

// SJF Non-Preemptive
void sjf(vector<Process> procs) {
    int n = procs.size();
    vector<bool> done(n, false);
    vector<GanttBlock> gantt;
    vector<Result> results;
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && procs[i].arrival <= time && procs[i].burst < minBurst) {
                minBurst = procs[i].burst;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        gantt.push_back({procs[idx].id, time, time + procs[idx].burst});
        time += procs[idx].burst;
        done[idx] = true;
        completed++;
        int ct = time, tat = ct - procs[idx].arrival, wt = tat - procs[idx].burst;
        results.push_back({procs[idx].id, procs[idx].arrival, procs[idx].burst, ct, tat, wt});
    }

    sort(results.begin(), results.end(), [](const Result& a, const Result& b) {
        return a.pid < b.pid;
    });

    printJSON("SJF (Non-Preemptive)", gantt, results);
}

// Round Robin
void roundRobin(vector<Process> procs, int quantum) {
    int n = procs.size();
    sort(procs.begin(), procs.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    vector<int> remaining(n);
    for (int i = 0; i < n; i++) remaining[i] = procs[i].burst;

    vector<GanttBlock> gantt;
    vector<Result> results(n);
    queue<int> q;
    vector<bool> inQueue(n, false);
    int time = 0, completed = 0;

    q.push(0); inQueue[0] = true;

    while (completed < n) {
        if (q.empty()) {
            time++;
            for (int i = 0; i < n; i++)
                if (!inQueue[i] && remaining[i] > 0 && procs[i].arrival <= time)
                    { q.push(i); inQueue[i] = true; }
            continue;
        }

        int idx = q.front(); q.pop();
        int execTime = min(quantum, remaining[idx]);
        gantt.push_back({procs[idx].id, time, time + execTime});
        time += execTime;
        remaining[idx] -= execTime;

        for (int i = 0; i < n; i++)
            if (!inQueue[i] && remaining[i] > 0 && procs[i].arrival <= time)
                { q.push(i); inQueue[i] = true; }

        if (remaining[idx] == 0) {
            completed++;
            int ct = time, tat = ct - procs[idx].arrival, wt = tat - procs[idx].burst;
            results[idx] = {procs[idx].id, procs[idx].arrival, procs[idx].burst, ct, tat, wt};
        } else {
            q.push(idx);
        }
    }

    sort(results.begin(), results.end(), [](const Result& a, const Result& b) {
        return a.pid < b.pid;
    });

    printJSON("Round Robin (Quantum=" + to_string(quantum) + ")", gantt, results);
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> procs(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        procs[i].id = i + 1;
        cout << "P" << i+1 << " -> Arrival Time: ";
        cin >> procs[i].arrival;
        cout << "P" << i+1 << " -> Burst Time:   ";
        cin >> procs[i].burst;
        procs[i].remaining = procs[i].burst;
    }

    int quantum;
    cout << "Enter Time Quantum for Round Robin: ";
    cin >> quantum;

    cout << "\n========== FCFS ==========\n";
    fcfs(procs);

    cout << "\n========== SJF (Non-Preemptive) ==========\n";
    sjf(procs);

    cout << "\n========== Round Robin ==========\n";
    roundRobin(procs, quantum);

    return 0;
}
