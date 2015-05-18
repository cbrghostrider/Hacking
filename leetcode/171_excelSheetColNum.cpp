class Solution {
public:
    int titleToNumber(string s) {
        return std::accumulate(s.begin(), s.end(), 0, [](const int& acc, const char& ch) -> int {
            return (acc*26 + (toupper(ch)-'A'+1));
        });
    }
};
