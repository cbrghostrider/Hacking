using MaxHeap = priority_queue<int, vector<int>, std::greater<int>>;
class Solution {
public:
    int matrixSum(vector<vector<int>>& nums) {
        const int R=nums.size();
        const int C=nums[0].size();
        vector<MaxHeap> heaps(R, MaxHeap());
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                heaps[r].push(nums[r][c]);
            }
        }
        int score=0;
        for (int c=0; c<C; c++) {
            int mnum = std::numeric_limits<int>::min();
            for (int r=0; r<R; r++) {
                int val = heaps[r].top();
                heaps[r].pop();
                mnum = std::max(mnum, val);
            }
            score += mnum;
        }
        return score;
    }
};
