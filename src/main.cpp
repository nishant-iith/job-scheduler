#include "../include/Simulator.h"
#include "../include/FCFSScheduler.h"
#include "../include/SJFScheduler.h"
#include "../include/RoundRobinScheduler.h"
#include "../include/PriorityScheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

std::vector<Job> loadJobs(const std::string& filename) {
    std::vector<Job> jobs;
    std::ifstream file(filename);
    std::string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        std::stringstream ss(line);
        int id, arrival, burst, priority;
        char comma;
        ss >> id >> comma >> arrival >> comma >> burst >> comma >> priority;
        jobs.emplace_back(id, arrival, burst, priority);
    }
    return jobs;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " --algorithm [FCFS|SJF|RR|PRIORITY] --input jobs.csv [--quantum N]\n";
        return 1;
    }

    std::string algorithm, inputFile;
    int quantum = 2; // Default time quantum
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--algorithm" && i + 1 < argc)
            algorithm = argv[++i];
        else if (std::string(argv[i]) == "--input" && i + 1 < argc)
            inputFile = argv[++i];
        else if (std::string(argv[i]) == "--quantum" && i + 1 < argc)
            quantum = std::stoi(argv[++i]);
    }

    std::vector<Job> jobs = loadJobs(inputFile);
    std::unique_ptr<Scheduler> scheduler;

    if (algorithm == "FCFS")
        scheduler = std::make_unique<FCFSScheduler>();
    else if (algorithm == "SJF")
        scheduler = std::make_unique<SJFScheduler>();
    else if (algorithm == "RR")
        scheduler = std::make_unique<RoundRobinScheduler>(quantum);
    else if (algorithm == "PRIORITY")
        scheduler = std::make_unique<PriorityScheduler>();
    else {
        std::cout << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }

    Simulator sim(std::move(scheduler), jobs);
    sim.run();
    sim.reportMetrics();
    sim.printGanttChart();

    return 0;
}