// 
// Extremely elegant and obvious solution.
// I don't know why this problem took so long and my earlier solution was so convoluted.
// Had a brain fart I suppose...
//
class Solution {
  public:
    // O(n) time, O(n) space.
    string removeDuplicates(string s, int k) {
        vector<pair<char, int>> lcounts;
        for (int i=0; i<s.size(); i++) {
            if (lcounts.empty() || lcounts.back().first != s[i]) {
                lcounts.push_back({s[i], 1});
            } else {
                lcounts.back().second += 1;
            }
            if (!lcounts.empty() && lcounts.back().second == k) {
                lcounts.pop_back();
            }
        }
        string ans;
        for (const auto& kv : lcounts) {
            ans += string(kv.second, kv.first);
        }
        return ans;
    }
};
