#include "../include/RoundRobinScheduler.h"

RoundRobinScheduler::RoundRobinScheduler(int quantum)
    : timeQuantum(quantum) {}

void RoundRobinScheduler::addJob(const Job& job) {
    rrQueue.push(job);
}

Job RoundRobinScheduler::getNextJob() {
    if (rrQueue.empty()) {
        return Job(-1, 0, 0, 0);
    }
    Job job = rrQueue.front();
    rrQueue.pop();
    return job;
}

bool RoundRobinScheduler::hasJobs() const {
    return !rrQueue.empty();
}

void RoundRobinScheduler::schedule(int currentTime) {
    // Round Robin: jobs are processed in timeQuantum slices
    // Actual logic handled in Simulator
}

RoundRobinScheduler::~RoundRobinScheduler() {}