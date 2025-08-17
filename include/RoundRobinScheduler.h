#pragma once

#include "Scheduler.h"
#include <queue>

class RoundRobinScheduler : public Scheduler {
public:
    RoundRobinScheduler(int quantum);
    void addJob(const Job& job) override;
    Job getNextJob() override;
    bool hasJobs() const override;
    void schedule(int currentTime) override;
    ~RoundRobinScheduler() override;

private:
    std::queue<Job> rrQueue;
    int timeQuantum;
};