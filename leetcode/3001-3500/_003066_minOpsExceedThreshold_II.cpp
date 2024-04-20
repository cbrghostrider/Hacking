class Solution {
typedef std::priority_queue<long, vector<long>, std::greater<long>> MinHeap;
public:
    int minOperations(vector<int>& nums, int k) {
        MinHeap mh;
        for (int n : nums) {mh.push(n);}
        int ops=0;
        while (mh.size() >= 2) {            
            if (mh.top() >= k) break;
            long x = mh.top(); mh.pop();
            long y = mh.top(); mh.pop();
            long z = x * 2 + y;
            mh.push(z);
            ops++;
        }
        return ops;
    }
};
