class Solution {
public:
    // O(n) time, O(n) space.
    // Using a monotonic stack.
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> stack, ans;
        vector<bool> computed;  // says whether ans was computed for that index, required during fixup step at the end.
        
        ans = vector<int>(nums.size(), 0);
        computed = vector<bool>(nums.size(), false);
        
        int greatest = -1000000000;
        
        // We run through the algorithm twice, to account for the wrap around.
        // The second time around, only unwritten answers are updated.
        for (int j=0; j<2; j++) {
            for (int i=nums.size()-1; i>=0; i--) {
                if (computed[i]) {continue;}  // for second time around
                
                while (!stack.empty() && stack.back() <= nums[i]) {  stack.pop_back(); }
                if (!stack.empty()) {
                    computed[i] = true;
                    ans[i] = stack.back();
                }
                
                stack.push_back(nums[i]);
                if (nums[i] > greatest) {greatest = nums[i];}
            }
        }
        
        // fixup step to account for rotation
        // degenerate case is when original array is reverse sorted, so nothing was written previously
        for (int i=0; i<nums.size(); i++) {
            if (computed[i]) continue;
            ans[i] = -1;
        }
        
        return ans;
    }
};
