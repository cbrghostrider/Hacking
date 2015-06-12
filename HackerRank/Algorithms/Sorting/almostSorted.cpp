// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void readInput(vector<int>& nums) {
    int n, k;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        std::cin >> k;
        nums.push_back(k);
    }
}

vector<bool> getStatus(const vector<int>& nums, int& earliest, int& latest, int& count) {
    //is this element bigger than the prev?
    vector<bool> status(nums.size(), false);
    status[0] = true;
    
    for (int i=1; i<nums.size(); i++) {
        bool check = nums[i] >= nums[i-1];
        if (check) {
            status[i] = true;
            continue;
        }

        //either i or i-1 is out of place
        bool check_i_pos_im2 = (i-2) < 0 ? true : nums[i] >= nums[i-2]; 
        int outofplace = i;
        if (check_i_pos_im2) {
            outofplace = i-1;
            status[i] = true;
        }
        status[outofplace] = false;

        count++;
        if (earliest == -1) earliest = outofplace;
        latest = outofplace;
    }
    return status;
}

void checkStatusForSwap1(const vector<int>& nums, int latest) {
    if (latest == nums.size()-1 && nums[latest] > nums[latest-2]) {
        std::cout << "yes" << std::endl;
        std::cout << "swap "<< latest << " " << latest+1 << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }    
}

void checkStatusForSwap2(const vector<int>& nums, int earliest, int latest, int count) {
    bool latestrelnprev   = earliest == 0             ? true : nums[latest] >= nums[earliest-1];
    bool latestrelnnext   = nums[latest] <= nums[earliest+1];
    bool earliestrelnprev = nums[earliest] >= nums[latest-1];
    bool earliestrelnnext = latest == nums.size() - 1 ? true : nums[earliest] <= nums[latest+1];
    if(latestrelnprev && latestrelnnext && earliestrelnprev && earliestrelnnext) {
        std::cout << "yes" << std::endl;
        std::cout << "swap "<< earliest+1 << " " << latest+1 << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
}

bool checkReversed(const vector<int>& nums, int earliest, int latest){
    bool reversed=true;
    for (int i=earliest+1; i<=latest; i++) {
        if (nums[i-1] < nums[i]) {
            reversed = false;
            break;
        }
    }
    return reversed;
}
   
int main() {
    vector<int> nums;
    readInput(nums);
    
    if (nums.size() <= 1) {
        std::cout << "yes" << std::endl;
        return 0;
    }
    if (nums.size() == 2) {
        std::cout << "yes" << std::endl;
        if (nums[0] > nums[1]) std::cout << "swap 1 2" << std::endl;
        return 0;
    }
    
    int earliest=-1, latest=-1, count=0;
    vector<bool> status = getStatus(nums, earliest, latest, count);
    
    //already sorted
    if (count == 0) {
        std::cout << "yes" << std::endl;
        return 0;
    } 
    
    if (count == 1) {
        checkStatusForSwap1(nums, latest);
        return 0;
    }
    
    if (count == 2) {
        checkStatusForSwap2(nums, earliest, latest, count);
        return 0;
    }
    
    bool reversed = checkReversed(nums, earliest, latest);
    if (reversed) {
        bool checkAgainstEarliestPrev = nums[latest] >= nums[earliest-1];
        bool checkAgainstEarliestPrevPrev = earliest <= 1 ? true : nums[latest] >= nums[earliest-1-1];
        if (checkAgainstEarliestPrev || checkAgainstEarliestPrevPrev) {
            std::cout << "yes" << std::endl;
            int init = checkAgainstEarliestPrev ? earliest+1 : earliest;
            std::cout << "reverse " << init << " " << latest+1 << std::endl;
            return 0;
        }
    }
    std::cout << "no" << std::endl;
    return 0;
}

