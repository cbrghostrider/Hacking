// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    unordered_map<int, int> seen;
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> repeats;
        for (const int& n : nums) {
            auto it = seen.find(n);
            if (it == seen.end()) {
                seen.insert(make_pair(n, 1));
            } else {
                seen[n]++;
            }
        }
        for (const pair<int, int>& s : seen) {
            if (s.second == 1) {
                repeats.push_back(s.first);
            }
        }
        return repeats;
    }
};
