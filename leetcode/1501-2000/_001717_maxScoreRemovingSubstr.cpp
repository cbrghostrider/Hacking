class Solution {

public:

    int eliminate(string s, string d1, int v1, string d2, int v2) {
        int total = 0;
        string s2;
        s2.push_back(s[0]);
        for (int i=1; i<s.size(); i++) {
            if (!s2.empty() && s2.back() == d1[0] && s[i] == d1[1]) {
                total += v1;
                s2.pop_back();
            } else {
                s2.push_back(s[i]);
            }
        }
        if (s2.empty()) return total;

        string s3;
        s3.push_back(s2[0]);
        for (int i=1; i<s2.size(); i++) {
            if (!s3.empty() && s3.back() == d2[0] && s2[i] == d2[1]) {
                total += v2;
                s3.pop_back();
            } else {
                s3.push_back(s2[i]);
            }
        }
        return total;
    }

    int maximumGain(string s, int x, int y) {
        if (s.size() <= 1) return 0;
        if (s.size() == 2 && s == "ab") return x;
        if (s.size() == 2 && s == "ba") return y;

        if (x > y) {
            return eliminate(s, "ab", x, "ba", y);
        }
        if (x < y) {
            return eliminate(s, "ba", y, "ab", x);
        }
        int v1 = eliminate(s, "ab", x, "ba", y);
        int v2 = eliminate(s, "ba", y, "ab", x);
        return std::max(v1, v2);
    }
};
