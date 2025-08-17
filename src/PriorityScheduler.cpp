#include "../include/PriorityScheduler.h"

PriorityScheduler::PriorityScheduler(int agingThreshold, int agingIncrement)
    : agingThreshold(agingThreshold), agingIncrement(agingIncrement) {}

void PriorityScheduler::addJob(const Job& job) {
    priorityQueue.push_back(job);
}

Job PriorityScheduler::getNextJob() {
    if (priorityQueue.empty()) {
        return Job(-1, 0, 0, 0);
    }
    // Find job with highest priority (lowest priority value)
    auto it = std::min_element(priorityQueue.begin(), priorityQueue.end(),
        [](const Job& a, const Job& b) {
            return a.priority < b.priority;
        });
    Job job = *it;
    priorityQueue.erase(it);
    return job;
}

bool PriorityScheduler::hasJobs() const {
    return !priorityQueue.empty();
}

void PriorityScheduler::schedule(int currentTime) {
    applyAging(currentTime);
    // Sort by priority, only those that have arrived
    std::sort(priorityQueue.begin(), priorityQueue.end(),
        [](const Job& a, const Job& b) {
            return a.priority < b.priority;
        });
}

void PriorityScheduler::applyAging(int currentTime) {
    for (auto& job : priorityQueue) {
        if (currentTime - job.arrivalTime > agingThreshold) {
            job.priority -= agingIncrement; // Lower value = higher priority
            if (job.priority < 0) job.priority = 0;
        }
    }
}

PriorityScheduler::~PriorityScheduler() {}