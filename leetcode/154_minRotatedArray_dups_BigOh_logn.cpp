// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//same solution as non-duplicate one, just got rid of duplicates 
//and did some checks for begin->end rollovers
class Solution {
private:
    bool isMinElement(vector<int>& nums, int size, int i) { //compared to both my neighbors, am I min
        bool evalPrev = (i == 0) ? (nums[i] <= nums[size-1]) : (nums[i] < nums[i-1]);
        bool evalNext = (i == (size - 1)) ? (nums[i] <= nums[0]) : (nums[i] < nums[i+1]);
        if (evalPrev && evalNext) return true ; else return false;
    }
    
    int binarySearchMinima(vector<int>& nums, int size, int lb, int ub) {
        if ((lb == ub) || ((lb + 1) == ub)) { //base cases
            if (isMinElement(nums, size, lb)) {
                return nums[lb];
            } else if (isMinElement(nums, size, ub)) {
                return nums[ub];
            }
            return -1; // error?
        }
        int mid = (lb + ub)/2;
        if (isMinElement(nums, size, mid)) {
            return nums[mid];
        } else if (nums[mid] > nums[ub]) {
            return binarySearchMinima(nums, size, mid, ub);
        } else {
            return binarySearchMinima(nums, size, lb, mid);
        }
    }
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 0) {
            return -1; //undefined
        }
        
        int check = nums[0];
        if (all_of(nums.begin(), nums.end(), [check] (const int& n) -> bool {return (n == check);})) {
            return nums[0];
        }
        
        //since it has duplicates, first get rid of them
        auto it = unique(nums.begin(), nums.end());
        
        //and find new size
        int size = it - nums.begin();
        
        //because unique only got rid of adjacent duplicates, not duplicates across the end->beginning
        if (nums[0] == (*(it-1))) size -= 1; 
        
        return binarySearchMinima(nums, size, 0, size-1);
    }
};
