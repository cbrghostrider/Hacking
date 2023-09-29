class Solution {
    // A candidate set, that adds up to the sum we want.
    // Records nums and their original indices from the input array.
    struct Cand {
        vector<int> nums;
        unordered_set<int> indices;
    };
    vector<Cand> all_cands;
    
    int getCsum(const vector<int>& nums) {
        int sum=0;
        for (int n : nums) {sum += n;}
        return sum;
    }
    
    // returns all subsets of the array that lead up to sss total sum
    // (might use the same elem in two different answers)
    // e.g. [1,1,2,2,4] (sss == 4) can return:
    // [1, 1, 2], [1, 1, 2], [2, 2], [4]
    // However note that ONLY PROPER candidates are generated (those adding to sss).
    vector<Cand> allSubsetsSSS(vector<int> nums, int sss) {
        int csum = getCsum(nums);
        if (sss == 0) return {Cand()};
        
        if (csum == sss) {
            Cand ret;
            ret.nums = nums;
            for (int i=0; i<nums.size(); i++) {ret.indices.insert(i);}
            return {ret};
        }
        
        if (nums.size() == 0 || csum < sss) {return {};}                
        
        int elem = nums.back(); 
        int elem_index = nums.size()-1;
        nums.pop_back();
        
        // Take it.
        vector<Cand> ss1, ss2;
        if (elem <= sss) {
            ss1 = allSubsetsSSS(nums, sss-elem);
            for (auto& ss : ss1) {
                ss.nums.push_back(elem);
                ss.indices.insert(elem_index);
            }
        }
        
        // Drop it.
        ss2 = allSubsetsSSS(nums, sss);
        
        ss1.insert(ss1.end(), ss2.begin(), ss2.end());
        return ss1;
    }
    
    // says whether we can choose k Cands from indices [0..n] of all_cands,
    // such that (VERY IMPORTANT):
    // all indices from 0..last_index are used, and none are re-used
    bool canChoose(int n, unordered_set<int> gone, int k, int last_index) {
        if (k == 0) { return gone.size() == (last_index+1);}
        if (n < 0 ) {return false;}
        
        for (int i=n; i>=0; i--) {
            unordered_set<int> gone_copy = gone;
            const Cand& cand = all_cands[i];
            bool can_choose = true;
            for (int ind : cand.indices) {
                if (gone.find(ind) != gone.end()) {
                    can_choose = false; break;
                } else {
                    gone_copy.insert(ind);
                }
            }
            if (!can_choose) {continue;}
            if (canChoose(i-1, gone_copy, k-1, last_index)) return true;
        }
        return false;
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if (nums.size() < k ) return false;
        int sum=getCsum(nums);
        if (sum % k != 0) return false;
        int subsetsum = sum/k;
        
        auto& ac = all_cands;
        all_cands = allSubsetsSSS(nums, subsetsum);
        
        unordered_set<int> gone;
        bool ret = canChoose(all_cands.size()-1, gone, k, nums.size()-1);
        return ret;
    }
};
