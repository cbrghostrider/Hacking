class Solution {
public:
    // O(nlogn) solution
    vector<int> sortArrayByParity2(vector<int>& nums) {
        vector<int> ans = nums;
        std::sort(ans.begin(), ans.end(), [](int left, int right) -> bool {
            if ((left % 2 == 1) && (right % 2 == 0)) {
                return false;
            } else if ((left % 2 == 0) && (right % 2 == 1)) {
                return true;
            }
            return (left < right);
        });
        return ans;
    }
    
    // O(n) solution.
    vector<int> sortArrayByParity(vector<int>& nums) {
        int even_end = 0, odd_end = nums.size()-1;
        vector<int> ans(nums.size(), 0);
        for (int n : nums) {
            if (n%2 == 0) {
                ans[even_end++] = n;
            } else {
                ans[odd_end--] = n;
            }
            
        }
        return ans;
    }
};
