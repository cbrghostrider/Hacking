class Solution {
public:
    // O(n log n) time, O(n) space.
    int minOperations(vector<vector<int>>& grid, int x) {
        
        const int R=grid.size();
        const int C=grid[0].size();
        
        vector<int> nums;        
        nums.reserve(R*C);
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                nums.push_back(grid[r][c]);                
            }            
        }
        std::sort(nums.begin(), nums.end());
        int median = nums[nums.size()/2];
        
        int ops=0;
        for (int n : nums) {
            int diff = std::abs(n - median);            
            if (diff % x != 0) return -1;
            ops += diff/x;
        }
        return ops;
    }
};
