class Solution {
public:
    // O(n^3) time, O(n) space.
    int countQuadruplets(vector<int>& nums) {
        std::unordered_map<int, int> counts, icounts, jcounts, kcounts;
        for (int n: nums) counts[n]++;
        
        int count = 0;
        icounts = counts;
        for (int i=0; i<nums.size(); i++) {
            icounts[nums[i]]--;
            jcounts = icounts;
            for (int j=i+1; j<nums.size(); j++) {
                jcounts[nums[j]]--;
                kcounts = jcounts;
                for (int k=j+1; k<nums.size(); k++) {
                    kcounts[nums[k]]--;
                    int target = nums[i] + nums[j] + nums[k];
                    if (kcounts[target] > 0) count += kcounts[target];
                }
            }
        }
        return count;
    }
};
