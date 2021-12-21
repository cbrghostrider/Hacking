class Solution {
    vector<int> best_sequence;
    
    vector<int> compare(const vector<int>& s1, const vector<int>& s2) {
        for (int i=0; i<s1.size(); i++) {
            if (s1[i] > s2[i]) return s1;
            if (s1[i] < s2[i]) return s2;
        }
        return s1;
    }
    
    bool place(vector<int>& nums, int k) {
        if (k == 1) {
            for (int i=0; i<nums.size(); i++) {
                if (nums[i] == -1) {
                    nums[i] = 1;
                    if (best_sequence.size() == 0) {
                        best_sequence = nums;
                    } else {
                        best_sequence = compare(best_sequence, nums);
                    }
                    nums[i] = -1;
                }
            }
            return false;  // should not happen
        }
        
        for (int i=0; i<nums.size(); i++) {
            if (i + k >= nums.size()) continue;
            if (nums[i] != -1 || nums[i+k] != -1) continue;
            
            // will try placing at i.
            nums[i] = k; nums[i+k] = k;
            place(nums, k-1);
            
            // Backtrack! Unplace and try again.
            nums[i] = -1; nums[i+k] = -1;
        }
        return false;
    }
    
public:
    vector<int> constructDistancedSequence(int n) {
        int num_nums = 2*n - 1;
        vector<int> ans(num_nums, -1);
        
        // place n deliberately at i==0, since the best sequence will for sure have this
        // then only backtrack n-1 onwards
        ans[0] = ans[0+n] = n;
        
        place(ans, n-1);
        return best_sequence;
    }
};
