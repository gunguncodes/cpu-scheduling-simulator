# CPU Scheduling Simulator

A mini project for the **Operating Systems** course that simulates three fundamental CPU scheduling algorithms - **FCFS**, **SJF (Non-Preemptive)**, and **Round Robin**  with a web-based Gantt chart visualizer.

---

## Algorithms Implemented

| Algorithm | Type | Description |
|-----------|------|-------------|
| FCFS | Non-Preemptive | Processes execute in order of arrival |
| SJF | Non-Preemptive | Shortest burst time process executes first |
| Round Robin | Preemptive | Each process gets a fixed time quantum cyclically |

---

## Project Structure

```
cpu-scheduling-simulator/
│
├── scheduler.cpp     # C++ backend — runs all 3 algorithms, outputs JSON
├── index.html        # Web visualizer — Gantt chart + metrics table
└── README.md
```

---

## How to Run

### Step 1 - Compile the C++ program
```bash
g++ scheduler.cpp -o scheduler
```

### Step 2 - Run the program
```bash
./scheduler
```
Enter the number of processes, arrival time, burst time for each process, and the time quantum for Round Robin when prompted.

### Step 3 - Copy the JSON output
The program prints JSON output for each algorithm in the terminal. Copy any one JSON block.

### Step 4 - Open the visualizer
Open `index.html` in any browser (just double-click it). Paste the JSON into the text box and click **Visualize**.

You can load results from all 3 algorithms one by one — the page will automatically generate a **comparison table**.

---

## Sample Input

```
Enter number of processes: 4
P1 -> Arrival Time: 0
P1 -> Burst Time: 5
P2 -> Arrival Time: 1
P2 -> Burst Time: 3
P3 -> Arrival Time: 2
P3 -> Burst Time: 8
P4 -> Arrival Time: 3
P4 -> Burst Time: 6
Enter Time Quantum for Round Robin: 2
```

---

## Sample Output (FCFS)

| Process | Arrival | Burst | Completion | Turnaround | Waiting |
|---------|---------|-------|------------|------------|---------|
| P1 | 0 | 5 | 5 | 5 | 0 |
| P2 | 1 | 3 | 8 | 7 | 4 |
| P3 | 2 | 8 | 16 | 14 | 6 |
| P4 | 3 | 6 | 22 | 19 | 13 |
| **Average** | - | - | - | **11.25** | **5.75** |

---

## Visualizer Features

- Color-coded Gantt chart with proportional block widths
- Metrics table showing Completion Time, Turnaround Time, Waiting Time
- Average waiting time and turnaround time per algorithm
- CPU utilization percentage
- Algorithm comparison table (auto-generated when multiple results are loaded)
- Sample data button for instant demo

---

## Tech Stack

- **C++** - Scheduling logic and JSON output
- **HTML / CSS / JavaScript** - Browser-based visualizer
- **g++ (MinGW)** - Compiler

---

## Requirements

- g++ compiler (`g++ --version` to check)
- Any modern browser (Chrome, Firefox, Edge)
- No external libraries or installations needed

---

## Subject Details

- **Course:** Operating Systems
- **Semester:** 3rd Semester
- **Branch:** B.Tech Computer Science and Engineering

---

## Author

**Gungun Kumari**  
B.Tech CSE Sarala Birla University  
GitHub: gunguncodes(https://github.com/gunguncodes)

