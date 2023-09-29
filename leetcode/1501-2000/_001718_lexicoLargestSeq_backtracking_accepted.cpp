class Solution {
    vector<int> place(vector<int>& nums, vector<int>& cands) {
        if (cands.size() == 1) {  
            for (int i=0; i<nums.size(); i++) {
                bool check_i = (nums[i] == -1);
                bool check_ovf = (cands[0] == 1 || i+cands[0] < nums.size());
                bool check_i_p_k = (cands[0] == 1 || (check_ovf && nums[i+cands[0]] == -1));
                if (check_i && check_i_p_k) {
                    if (cands[0] == 1) nums[i] = 1;
                    else {nums[i] = nums[i + cands[0]] = cands[0];}
                    return nums;
                }
            }
            return {};
        }
        
        int chosen = -1;  // most significant place to be filled
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] != -1) continue;
            chosen = i;
            break;
        }
                
        for (int ki=0; ki<cands.size(); ki++) {
            int k=cands[ki];
            // if (k == 1) return {};  // should always be placed last
            if (k != 1 && chosen+k >= nums.size()) continue;
            if (k != 1 && nums[chosen+k] != -1) continue;
                
            // will try placing at k at chosen
            nums[chosen] = k;
            if (k != 1) nums[chosen+k] = k;
            cands.erase(begin(cands) + ki);
            auto ans = place(nums, cands);
            if (ans.size() != 0) return ans;
            
            // Backtrack! Unplace and try again.
            nums[chosen] = -1;
            if (k != 1) nums[chosen+k] = -1;
            cands.insert(begin(cands) + ki, k);
        }
        return {};
    }
    
public:
    //
    // The following is the KEY DIFFERENCE between this backtracking and
    // the previous backtracking solution, which causes this one to be accepted
    // but causes TLE in the previous solution.
    //
    // Previous solution, we placed the NUMBERS from biggest to smallest
    // This solution, we place INDICES from most significant to least significant.
    //
    // By placing the best number possible (may need to iterate to find it)
    // at the highest possible index at the time (leftmost with -1 value)
    // we ENSURE that the VERY FIRST SOLUTION FOUND IS THE BEST SOLUTION!
    //
    // Therefore we don't need to search the whole search space. :-)
    //
    vector<int> constructDistancedSequence(int n) {
        int num_nums = 2*n - 1;
        vector<int> ans(num_nums, -1);
        
        vector<int> cands;
        for (int i=n; i>=1; i--) {cands.push_back(i);}
        
        return place(ans, cands);
    }
};
