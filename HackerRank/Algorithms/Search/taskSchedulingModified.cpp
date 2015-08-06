// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Note: This solution does NOT solve the actual problem. 
//
// I misread the problem, and solved the following (new) problem instead:
//    "Minimize the maximum amount of overshoot, when all tasks are scheduled." 
//    i.e. if 5 tasks were scheduled with overshoots O1 O2 O3 O4 O5, 
//    schedule them such that the max(O1, O2, O3, O4, O5) is minimized. Sad face.
//
// i.e. This solution is minimizing the maximum overshoot time.

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <assert.h>

using std::vector;

// Assumption: Tasks can be broken up into integral number of minutes
class TaskScheduler {
public:
    TaskScheduler();
    void processOvershoots();
private:
    int computeCriteria(int index); 
    int chooseTask();
    bool scheduleMinute(int chosen);
    void writeOutputs();

    vector<int> dis; //task deadlines
    vector<int> mis; //task lengths
    vector<int> fis; //final finish times
    int curTime;     //for simulation
    int tasks;       //total number of tasks
};

TaskScheduler::TaskScheduler()
: dis(), mis(), fis(), curTime(0), tasks(0) {
    std::cin >> tasks;

    dis = vector<int>(tasks, 0);
    mis = vector<int>(tasks, 0);
    fis = vector<int>(tasks, 0);

    for (int i=0; i<tasks; i++) {
        int d, m; std::cin >> d >> m;
        dis[i] = d;
        mis[i] = m;
    }
}

//computes the greedy criterion for index
// Ci = (Di - curTime) - (Mi_remaining)
// Mi_remaining is time remaining for task i at that point
// (Di - curTime) represents how close this task is to its deadline
// Mi_remaining is the amount of minutes for this task still leftover
// can be negative.
int TaskScheduler::computeCriteria(int index) {
    return ((dis[index] - curTime) - mis[index]);
}

// choose a task per greedy criterion, whos minute will be scheduled
int TaskScheduler::chooseTask() {
    int chosen = -1;
    for (int i=0; i<tasks; i++) {
        if (mis[i] == 0) continue; //this task is already done

        if (chosen == -1 || computeCriteria(i) < computeCriteria(chosen)) {
            chosen = i;
        } else if (computeCriteria(i) == computeCriteria(chosen) && dis[i] < dis[chosen]) { //tie-breaker on earliest deadline
            chosen = i;
        }
    }
    assert(chosen != -1);
    return chosen;
}

bool TaskScheduler::scheduleMinute(int chosen) {
    std::cout << (chosen+1) << " ";
    mis[chosen]--;
    curTime++;
    if (mis[chosen] == 0) {
        fis[chosen] = curTime;
        return true;
    }
    return false;
}

void TaskScheduler::writeOutputs() {
    for (int i=0; i<tasks; i++) {
        int overshoot = fis[i] - dis[i];
        std::cout << (overshoot <= 0 ? 0 : overshoot) << std::endl;;
    }
}

void TaskScheduler::processOvershoots() {
    int tasksDone = 0;
    std::cout << "Task scheduling slots" << std::endl;
    while (tasksDone < tasks) {
        int chosen = chooseTask();
        bool taskDone = scheduleMinute(chosen);
        if (taskDone) { tasksDone++; }
    }
    std::cout << std::endl;
    writeOutputs();
}

int main() {
    TaskScheduler ts;
    ts.processOvershoots();
}
