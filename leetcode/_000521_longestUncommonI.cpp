class Solution {
public:
    int findLUSlength(string a, string b) {
        if (a == b) return -1;
        return std::max(a.size(), b.size());
    }
};
