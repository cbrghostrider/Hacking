// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// The problem with the straightforward O(n^2) DP solution is the inner for loop. 
// If the input array is reverse sorted array from [n...1, 1, 0] then the 
// algorithmic complexity will hit the worst case O(n^2). 
// This is indeed a test case, and I got TLE for this.
// 
// The solution to this problem is as follows. You will notice that the inner 
// for loop is doing a Range-Minimum-Query. i.e. it is checking all previous DP 
// results from 1 to nums[i] places from my current place (my jump range) and 
// taking the minimum. I can implement a Data Structure to perform range minimum query. 
// I implemented the array method, using sqrt(n) entries. But you can use 
// segment tree too I believe.
// 
// Anyway, the getmin method has complexity sqrt(n) and therefore overall complexity becomes O(n*sqrtn)
//
// algorithmic complexity is O(n*sqrtn)
// getmin has complexity O(sqrtn) (each loop is sqrtn)
//
// Solution uses range minimum query, using the sqrt method
//
class Solution {
    int NUMS;
    int RMQS;
    
    //dynamic programming cache
    vector<int> numJumps;
        
    //range minimum query array (stored backward) sqrt(R) chunk mins
    vector<int> rmq;
    
    //takes index into nums array, and returns index into rmq
    int getRmqIndex(int index) {
        return (index/RMQS);
    }
    
    //range minimum query between [from, to] indices
    int getMin(int from, int to) {
        int fromPrime = from+RMQS;
        int toPrime   = to-RMQS;
        int rmqFrom = getRmqIndex(fromPrime);
        int rmqTo   = getRmqIndex(toPrime);

        int minval = std::numeric_limits<int>::max();
        //min of leftmost chunk
        for (int i=from; i<=(rmqFrom*RMQS) && i<numJumps.size(); i++) {
            if (numJumps[i] < minval) minval = numJumps[i];
        }

        //min of rmq array ranged query
        for (int i=rmqFrom; i<=rmqTo; i++) {
            if (rmq[i] < minval) minval = rmq[i];
        }

        //min of rightmost chunk
        for (int i=((rmqTo + 1)*RMQS); i<=to && i >= from && i<numJumps.size(); i++) {
            if (numJumps[i] < minval) minval = numJumps[i];
        }
        return minval;
    }
    
    //update the rmq for the given index
    void updateRMQ(int index, int value) {
        int indexRmq = getRmqIndex(index);
        if (rmq[indexRmq] > value) {
            rmq[indexRmq] = value;
        }
    }
public:
    int jump(vector<int>& nums) {
        //pretend jumping from end to beginning, leftwards... makes indices easier for RMQ
        std::reverse(nums.begin(), nums.end());
        
        NUMS = nums.size();
        RMQS = ceil(sqrt(NUMS));
        
        rmq = vector<int>(RMQS+1, std::numeric_limits<int>::max());
        numJumps = vector<int>(NUMS, std::numeric_limits<int>::max());

        numJumps[0] = 0;
        updateRMQ(0, 0);
        
        //dynamic programming loop
        for (int i=1; i<NUMS; i++) {
            if (nums[i] <= 0) {
                numJumps[i] = std::numeric_limits<int>::max(); //not possible
                continue;
            }
            int from = ((i - nums[i]) < 0 ) ? 0 : (i-nums[i]);
            int to = i-1;

            int minval = getMin(from, to);
            int minJumps = (from == 0) ? 1 : (minval == std::numeric_limits<int>::max() ? minval : 1 + minval);
            numJumps[i] = minJumps;
            updateRMQ(i, minJumps);
        }
        
        return numJumps[NUMS-1];
    }
};

