// UIController.h
#pragma once

#include "Scheduler.h"
#include "FCFSScheduler.h"
#include "SJFScheduler.h"
#include "RoundRobinScheduler.h"
#include "PriorityScheduler.h"
#include "Job.h"
#include <vector>
#include <string>
#include <memory>

class UIController {
public:
    UIController();
    void runSession();

private:
    std::vector<Job> jobs;
    std::unique_ptr<Scheduler> scheduler;
    int currentAlgorithm; // 0:FCFS, 1:SJF, 2:RR, 3:Priority

    // Menu methods
    void showMainMenu();
    void handleMainMenuInput(int choice);
    void showJobMenu();
    void handleJobMenuInput(int choice);
    void showAlgorithmMenu();
    void handleAlgorithmMenuInput(int choice);
    void showVisualizationMenu();
    void handleVisualizationMenuInput(int choice);
    void showStatisticsMenu();
    void handleStatisticsMenuInput(int choice);
    void showHelpOverlay();

    // Job management
    void createJob();
    void editJob();
    void deleteJob();
    void importJobsCSV();
    void exportJobsCSV();

    // Scheduler integration
    void switchAlgorithm(int algo);
    void updateScheduler();

    // Visualization
    void displayGanttChart();
    void displayTimelineLog();

    // Statistics
    void displayStatistics();

    // Utility
    int getIntInput(const std::string& prompt, int min, int max);
    std::string getStringInput(const std::string& prompt);
    void clearScreen();
    void pause();
    void error(const std::string& msg);
};