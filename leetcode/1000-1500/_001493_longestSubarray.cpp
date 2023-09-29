class Solution {
public:
    // O(n) space, O(n) time.
    int longestSubarray(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        
        // Run lengths: stores (1/0, number of 1/0 consecutive)
        vector<std::pair<int, int>> run_lengths;
        const int N = nums.size();
        
        int l_ptr=0;
        int max=0;
        bool has_zero = false;
        
        while (l_ptr < N) {
            int r_ptr = l_ptr;
            while (r_ptr < N && nums[l_ptr] == nums[r_ptr]) {r_ptr++;}
            int len = r_ptr-l_ptr;
            run_lengths.push_back(std::make_pair(nums[l_ptr], len));
            if (nums[l_ptr] == 1 && max < len) {max = len;}
            if (nums[l_ptr] == 0) {has_zero = true;}
            l_ptr = r_ptr;
        }
        if (max == 0) return 0;
        
        
        for (int rl=0; rl<run_lengths.size(); rl++) {
            if (run_lengths[rl].first == 0) continue;
            if (rl < ((int)run_lengths.size())-2 &&  // there is a seq of 0's and then 1's after my seq of 1's
                run_lengths[rl+1].second == 1 // the seq of 0's only has 1 zero
                ) {
                int new_len = run_lengths[rl].second + run_lengths[rl+2].second;
                if (new_len > max) {
                    max = new_len;
                }
            }
        }
        return (has_zero ? max : max-1);  // have to delete a 1, if there are only 1's in the entire sequence
    }
};
