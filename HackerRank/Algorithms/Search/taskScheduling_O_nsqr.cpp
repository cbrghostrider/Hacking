// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// I could refactor my previous attempt to solve this
// The solution is functionally correct, passing 4/10 cases
// But it is slow O(n^2) and TLE on 6/10 cases.
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
    void processOvershoots(int index);
    int computeCriteria(int index); 
    int chooseTask(int index);
    bool scheduleMinute(int chosen);
    void writeOutputs(int index);

    vector<int> dis;    //task deadlines
    vector<int> mis;    //task lengths
    vector<int> mirems; //task lengths remaining
    vector<int> fis;    //final finish times
    int curTime;        //for simulation
    int tasks;          //total number of tasks
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
    return ((dis[index] - curTime) - mirems[index]);
}

// choose a task per greedy criterion, whos minute will be scheduled
//only considers tasks up to index
int TaskScheduler::chooseTask(int index) {
    int chosen = -1;
    for (int i=0; i<index; i++) {
        if (mirems[i] == 0) continue; //this task is already done

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
    //std::cout << (chosen+1) << " ";
    mirems[chosen]--;
    curTime++;
    if (mirems[chosen] == 0) {
        fis[chosen] = curTime;
        return true;
    }
    return false;
}

void TaskScheduler::writeOutputs(int index) {
    int maxovershoot = 0;
    for (int i=0; i<index; i++) {
        int overshoot = fis[i] - dis[i];
        if (overshoot > 0 && overshoot > maxovershoot) {
            maxovershoot = overshoot;
        }
    }
    std::cout << maxovershoot << std::endl;;
}

//consider tasks only up to index
void TaskScheduler::processOvershoots(int index) {
    //init various state
    int tasksDone = 0;
    curTime = 0;
    mirems = mis;
    fis = vector<int>(tasks, 0);

    //std::cout << "Task scheduling slots" << std::endl;
    while (tasksDone < index) {
        int chosen = chooseTask(index);
        bool taskDone = scheduleMinute(chosen);
        if (taskDone) { tasksDone++; }
    }
    //std::cout << std::endl;
    writeOutputs(index);
}

void TaskScheduler::processOvershoots() {
    for (int t=0; t<tasks; t++) {
        processOvershoots(t+1);
    }
}

int main() {
    TaskScheduler ts;
    ts.processOvershoots();
}



