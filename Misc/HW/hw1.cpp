#include <iostream>
#include <utility> 
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <assert.h>

//tuple of (wt, len)
typedef std::pair<int, int> Job;

void readInput(std::vector<Job>& jobs, const char* fileName)
{
    std::string line;
    std::ifstream input(fileName);
    if (input.is_open()) {
        //read the size
        getline(input, line);

        while (getline(input, line)) {
            std::stringstream ss(line);
            int wt=0, len=0;
            ss >> wt >> len;
            jobs.push_back(std::make_pair(wt, len));
        }
        input.close();
    } else {
        std::cout << "Could not open" << fileName << std::endl;
    }
}

//comparison criteria for (wj - lj)
bool compareOnDiff(const Job& lhs, const Job& rhs)
{
    if ((lhs.first - lhs.second) < (rhs.first - rhs.second)) {
        return false;  //element with higher diff first
    } else if ((lhs.first - lhs.second) > (rhs.first - rhs.second)) {
        return true;   //element with higher diff first
    } else {
        //equal differences
        return (lhs.first > rhs.first); //element with weight goes first
    }
}

//comparison criteria for (wj/lj)
bool compareOnRatio(const Job& lhs, const Job& rhs)
{
    assert(lhs.second != 0 && rhs.second != 0);

    double lhsRatio = ((double)(lhs.first))/((double)(lhs.second));
    double rhsRatio = ((double)(rhs.first))/((double)(rhs.second));

    if (lhsRatio > rhsRatio) {
        return true;
    } else {
        return false;
    }
}

void scheduleJobs(std::vector<Job>& jobs, const char* type)
{
    if (type == std::string("ratio")) {
        std::sort(jobs.begin(), jobs.end(), compareOnRatio);
    } else {
        std::sort(jobs.begin(), jobs.end(), compareOnDiff);
    }
}

long long sumOfWeightedCompTimes(const std::vector<Job>& jobs)
{
    //first sum all timings
    long long totalTime=0;
    std::for_each(jobs.begin(), jobs.end(), [&totalTime] (const Job& j) -> void {
        totalTime += j.second;
    });

    //then go from end to start, computing weighted completion times
    long long wtCompTime=0;
    std::for_each(jobs.rbegin(), jobs.rend(), [&totalTime, &wtCompTime] (const Job& j) -> void {
        wtCompTime += (j.first) * totalTime;
        totalTime -= j.second;
    });

    return wtCompTime;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: ./progName inputFile scheduleType" << std::endl;
        std::cout << "     : scheduleType = ratio or diff"      << std::endl;
        return 1;
    }

    std::vector<Job> jobs;
    readInput(jobs, argv[1]);

    scheduleJobs(jobs, argv[2]);

    long long wtCompTime = sumOfWeightedCompTimes(jobs);
    std::cout << "Weighted comp time summed: " << wtCompTime << std::endl;
}



