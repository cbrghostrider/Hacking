class Solution {
public:
    // O(|order|) space, O(|s|) time.
    string customSortString(string order, string s) {
        unordered_map<char, int> rankings;
        for (int i=0; i<order.size(); i++) {rankings[order[i]] = i;}
        std::sort(s.begin(), s.end(), [&rankings](char lhs, char rhs) -> bool {
            return (rankings[lhs] < rankings[rhs]);
        });
        return s;
    }
};
