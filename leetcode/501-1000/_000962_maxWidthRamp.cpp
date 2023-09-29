class Solution {
    // Stores information for any contiguous chunk.
    struct Info {
        int best=0;     // the best width ramp discovered
        int min_val=0;  // the min value in this chunk
        int max_val=0;  // the max value in this chunk
    };
    
    Info process(const vector<int>& nums, int lo, int hi) {
        if (lo == hi) {return {0, nums[lo], nums[lo]};}
        if (lo+1 == hi) {
            bool non_decreasing = nums[lo] <= nums[hi];
            return {non_decreasing ? 1 : 0, 
                    non_decreasing ? nums[lo] : nums[hi],
                    non_decreasing ? nums[hi] : nums[lo]};
        }
        int mid = (lo+hi)/2;
        Info lhs = process(nums, lo, mid);
        Info rhs = process(nums, mid+1, hi);
        // TODO
        return {};
    }
public:
    // O(n log n) time, O(n) space.
    int maxWidthRamp(vector<int>& nums) {
        vector<int> indices;
        for (int i=0; i<nums.size(); i++) {
            indices.push_back(i);
        }
    
        std::sort(indices.begin(), indices.end(), [&nums](int lhs, int rhs) -> bool {
            if (nums[lhs] != nums[rhs]) return nums[lhs] < nums[rhs];
            return lhs < rhs;
        });
    
        int min_index=indices[0];
        int best=0;
        for (int i=1; i<indices.size(); i++) {
            if (min_index <= indices[i]) {
                best = std::max(best, indices[i]-min_index);
            } else {
                min_index = indices[i];
            }
        }
        return best;
    }

    
    int maxWidthRamp_2(vector<int>& nums) {
        int best=0;
        for (int left=0, right=nums.size()-1; left < nums.size() && right >= 0; left++, right--) {
            // check left with all right cands
            for (int check=nums.size()-1; check>=right; check--) {
                if (nums[left] <= nums[check]) {
                    best = std::max(best, check-left);                    
                }
            }
            // check right with all left cands
            for (int check=0; check<=left; check++) {
                if (nums[check] <= nums[right]) {
                    best = std::max(best, right-check);                    
                }
            }            
        }
        return best;
    }

    
    // O(n^2) time, O(n) space.
    int maxWidthRamp_(vector<int>& nums) {
        int best=0;
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                if (nums[i] <= nums[j]) {
                    int my_val = j-i;
                    best = std::max(my_val, best);
                }
            }
        }
        return best;
    }
};
