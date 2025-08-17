# CPU Job Scheduler (C++ CLI Project)

## Overview
A modular C++ simulation of CPU job scheduling algorithms (FCFS, SJF, Round Robin, Priority with aging). Includes CLI, job data file input, performance metrics, and Gantt chart output.

## File Structure
```
Scheduler/
├── src/
│   ├── Job.cpp
│   ├── FCFSScheduler.cpp
│   ├── SJFScheduler.cpp
│   ├── RoundRobinScheduler.cpp
│   ├── PriorityScheduler.cpp
│   ├── Simulator.cpp
│   └── main.cpp
├── include/
│   ├── Job.h
│   ├── Scheduler.h
│   ├── FCFSScheduler.h
│   ├── SJFScheduler.h
│   ├── RoundRobinScheduler.h
│   ├── PriorityScheduler.h
│   ├── Simulator.h
├── data/
│   └── jobs.csv
├── README.md
```

## Features
- FCFS, SJF (Preemptive), Round Robin, Priority (Preemptive with aging)
- CLI for algorithm selection and job file input
- Performance metrics: Average Turnaround Time, Average Waiting Time
- Text-based Gantt chart output

## How to Build & Run
1. Compile all `.cpp` files in `src/` with a C++17+ compiler:
   ```
   g++ -std=c++17 src/*.cpp -Iinclude -o scheduler_cli
   ```
2. Run the executable, providing the scheduler type and job file path as arguments:
   ```
   ./scheduler_cli --algorithm FCFS --input data/jobs.csv
   ./scheduler_cli --algorithm SJF --input data/jobs.csv
   ./scheduler_cli --algorithm RR --input data/jobs.csv --quantum 2
   ./scheduler_cli --algorithm PRIORITY --input data/jobs.csv
   ```

## Example Job File (`data/jobs.csv`)
```
id,arrival,burst,priority
1,0,5,2
2,2,3,1
3,4,1,3
4,6,2,2
```

## Usage
- Select the scheduling algorithm using `--algorithm`.
- Provide the job data file using `--input`.
- For Round Robin, specify the time quantum using `--quantum`.

## Extending
Add new scheduling algorithms by implementing the `Scheduler` interface and updating `main.cpp`.

## License
MIT