class Solution {
    int max=0;
    
public:
    
    void updateMax(int l_ptr, int r_ptr) {
        if (r_ptr - l_ptr > max) {
            max = r_ptr - l_ptr;
        }
    }
    
    int longestOnes(vector<int>& nums, int k) {
        int l_ptr=0, r_ptr=0;
        
        while (r_ptr < nums.size()) {
            if (nums[r_ptr] == 1) {
                r_ptr++;
                updateMax(l_ptr, r_ptr);
            } else if (nums[r_ptr] == 0 && k > 0) {
                k--;
                r_ptr++;
                updateMax(l_ptr, r_ptr);
            } else if (nums[l_ptr] == 1) {
                l_ptr++;
            } else if (nums[l_ptr] == 0) {
                k++;
                l_ptr++;
            }
        }
        return max;
    }
};
