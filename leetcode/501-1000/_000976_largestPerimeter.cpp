class Solution {
public:
    // O(nlogn) time, O(1) space.
    int largestPerimeter(vector<int>& nums) {
        if (nums.size() < 3) return 0;
        std::sort(nums.begin(), nums.end());
        
        for (int i=nums.size()-1; i>=2; i--) {
            int n1 = nums[i];
            int n2 = nums[i-1];
            int n3 = nums[i-2];
            if (n1 >= n2 + n3) continue;
            return n1+n2+n3;
        }
        return 0;
    }
};
