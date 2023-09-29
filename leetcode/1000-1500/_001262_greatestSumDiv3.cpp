class Solution {
    using MinHeap = priority_queue<int, vector<int>, std::greater<int>>;    
public:
    // O(n log n) time, O(n) space.
    // Can be optimized to O(n) and O(1) by only keeping 2 top entries in heap1 and heap2.
    int maxSumDivThree(vector<int>& nums) {
        MinHeap heap1, heap2;
        int sum=0;
        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
            if (nums[i] % 3 == 2) {heap2.push(nums[i]);}
            if (nums[i] % 3 == 1) {heap1.push(nums[i]);}
        }
        
        if (sum % 3 == 0) return sum;
        
        if (sum % 3 == 2) {
            int c2 = heap2.empty() ? -1 : heap2.top();
            int c11 =  -1;
            if (heap1.size() >= 2) {
                c11 = heap1.top(); heap1.pop();
                c11 += heap1.top(); heap1.pop();
            }
            return sum - (c2 == -1 ? c11 : c11 == -1 ? c2 : min(c11, c2));
        }
        
        // sum % 3 == 1
        int c1 = heap1.empty() ? -1 : heap1.top();
        int c22 =  -1;
        if (heap2.size() >= 2) {
            c22 = heap2.top(); heap2.pop();
            c22 += heap2.top(); heap2.pop();
        }
        return sum - (c1 == -1 ? c22 : c22 == -1 ? c1 : min(c22, c1));
    }
};
