// note that both the forward pointer (ind) and the back pointer (indElim) only move forward. 
// In particular, indElim never moves backward other than the minor decrement after increment. 
// In the worst case, both pointers move length O(n), and solution is O(n)
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        //if (nums.size() == 0) return 0;
        int total = std::accumulate(nums.begin(), nums.end(), 0, [] (const int& acc, const int& n) -> int {return (acc + n);});
        if (total < s) return 0;
        
        //contains for index i, (#elems, sum of elems) of subarr ending at i, such that
        //sum of these elems >=s or this is the sum of all elems from 0 up to index i
        pair<int, int> prev;
        prev = make_pair(1, nums[0]);
        int minLen = (nums[0] >= s) ? 1 : std::numeric_limits<int>::max();
        if (minLen == 1) return minLen;
        
        for (int ind=1; ind<nums.size(); ind++) {
            int numIndM1 = prev.first;
            int sumIndM1 = prev.second;
            int cNum     = numIndM1 + 1;
            int cSum     = sumIndM1 + nums[ind];
            int indElim  = ind - numIndM1;
            if (cSum >= s) {
                while (cSum >= s) {
                    cSum -= nums[indElim];
                    indElim++; 
                    cNum--;
                }
                cNum++;
                indElim--;
                cSum += nums[indElim];
                if (minLen > cNum) minLen = cNum;
            }
            prev = make_pair(cNum, cSum);
        }
        return minLen;
    }
};
