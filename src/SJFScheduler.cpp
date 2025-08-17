#include "../include/SJFScheduler.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

SJFScheduler::SJFScheduler() {}

void SJFScheduler::addJob(const Job& job) {
    sjfQueue.push_back(job);
}

Job SJFScheduler::getNextJob() {
    if (sjfQueue.empty()) {
        return Job(-1, 0, 0, 0);
    }
    // Find job with minimum remainingTime
    auto it = std::min_element(sjfQueue.begin(), sjfQueue.end(),
        [](const Job& a, const Job& b) {
            return a.remainingTime < b.remainingTime;
        });
    Job job = *it;
    sjfQueue.erase(it);
    return job;
}

bool SJFScheduler::hasJobs() const {
    return !sjfQueue.empty();
}

void SJFScheduler::schedule(int currentTime) {
    // SJF: sort jobs by remainingTime, only those that have arrived
    std::sort(sjfQueue.begin(), sjfQueue.end(),
        [](const Job& a, const Job& b) {
            return a.remainingTime < b.remainingTime;
        });
}

SJFScheduler::~SJFScheduler() {}

void SJFScheduler::setJobs(const std::vector<Job>& jobs) {
    sjfQueue = jobs;
    std::sort(sjfQueue.begin(), sjfQueue.end(), [](const Job& a, const Job& b) {
        return a.burstTime < b.burstTime;
    });
    scheduledJobs.clear();
    timelineLog.clear();
}

std::string SJFScheduler::getGanttChart() const {
    std::ostringstream oss;
    oss << "Gantt Chart:\n|";
    for (const auto& job : scheduledJobs) {
        oss << " " << job.getName() << " |";
    }
    oss << "\n";
    return oss.str();
}

std::string SJFScheduler::getTimelineLog() const {
    std::ostringstream oss;
    oss << "Timeline Log:\n";
    for (const auto& entry : timelineLog) {
        oss << entry << "\n";
    }
    return oss.str();
}

std::string SJFScheduler::getStatistics() const {
    std::ostringstream oss;
    double totalWT = 0, totalTT = 0;
    int count = scheduledJobs.size();
    oss << std::left << std::setw(10) << "Job"
        << std::setw(10) << "WT"
        << std::setw(10) << "TT" << "\n";
    for (const auto& job : scheduledJobs) {
        oss << std::setw(10) << job.getName()
            << std::setw(10) << job.waitingTime
            << std::setw(10) << job.turnaroundTime << "\n";
        totalWT += job.waitingTime;
        totalTT += job.turnaroundTime;
    }
    if (count > 0) {
        oss << "Avg WT: " << totalWT / count << "\n";
        oss << "Avg TT: " << totalTT / count << "\n";
    }
    return oss.str();
}