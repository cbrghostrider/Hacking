// Memoized DP solution (top-down).
// O(n^2) algorithm.
// Clears 1576/1582 test cases, rest TLE.
class Solution {
    struct Info {
        int diff;
        pair<int, int> indices;
    };
    unordered_set<int> htable;
    std::vector<Info> diffs;

    unordered_map<uint64_t, int> dp;

    uint64_t dpkey(uint64_t pval, uint64_t ind) {
        return ((pval << 32) | ind);
    }

    int solve(uint64_t pval, uint64_t ind) {
        uint64_t key = dpkey(pval, ind);
        auto it = dp.find(key);
        if (it != dp.end()) { return it->second;}   

        if (diffs.size() - ind == 2*pval-1) {
            int mdiff=0;
            for (int i=ind; i<diffs.size(); i+=2) {
                if (diffs[i].diff > mdiff) {mdiff = diffs[i].diff;}
            }
            dp[key] = mdiff;
            return mdiff;
        }

        // Choice 1: Pick ind.
        int choice1 = std::numeric_limits<int>::max();
        if (diffs.size() - ind - 2 >= pval-1) {
            int rec = solve(pval-1, ind+2);
            choice1 = std::max(diffs[ind].diff, rec);
        }

        // Choice 2: Drop ind.
        int choice2 = solve(pval, ind+1);

        int result = std::min(choice1, choice2);
        dp[key] = result;
        return result;
    }


public:    
    
    int minimizeMax(vector<int>& nums, int p) {
        if (p <=0) return 0;        
        std::sort(nums.begin(), nums.end());

        for (int i=0; i<nums.size()-1; i++) {
            int diff = std::abs(nums[i+1] - nums[i]);
            diffs.push_back({diff, make_pair(i, i+1)});
        }

        return solve(p, 0);
    }
};
