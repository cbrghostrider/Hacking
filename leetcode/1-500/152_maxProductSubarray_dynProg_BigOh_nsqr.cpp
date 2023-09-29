// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//Two tricks for space optimization:
//Trick 1: Since I only use last sz array, I can keep just a 2 dimensional array with first dimension[2]
//Trick 2: Since 1 is identity for multiplication, after recording max of array, 
//         and before dynamic programming I can delete all 1s
class Solution {
public:
    int maxProduct(vector<int>& numbers) {
        int max=std::numeric_limits<int>::min();     
        
        //remove all the 1s since 1 is identity for multiplication
        vector<int> nums;
        for (unsigned int i=0; i<numbers.size(); i++) {
            if (numbers[i] > max) max = numbers[i]; //do this before deleting the 1s
            if (numbers[i] != 1) nums.push_back(numbers[i]); 
        }
        if (nums.size() == 0) {
            return max;
        }
        
        //dynamic programming cache; c[i][j] is product of contiguous elements i starting at index j
        int **cache = new int*[2];
        cache[0] = new int[nums.size()];
        cache[1] = new int[nums.size()];
        
        //initialization
        for (unsigned int j=0; j<nums.size(); j++) {
            cache[1][j] = std::numeric_limits<int>::min();
            cache[0][j] = nums[j]; 
        }
        
        int prev = 0;
        int next = 1;
        
        //run dynamic programming alg
        for (unsigned int sz=2; sz<=nums.size(); sz++) {
            for (unsigned int i=0; i<nums.size() && (i+sz-1) < nums.size(); i++) {
                cache[next][i] = cache[prev][i+1] * nums[i]; 
                if (cache[next][i] > max) max = cache[next][i];
            }
            prev = 1 - prev;
            next = 1 - next;
        }
        
        //free memory
        delete cache[1]; delete cache[0]; delete cache;
        return max;
    }
};
