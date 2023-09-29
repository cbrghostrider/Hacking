class Solution {
public:
    int minTimeToType(string word) {
        char last = 'a';
        int total=0;
        for (char ch : word) {
            int c1 = last-ch;
            int c2 = ch-last;
            if (c1 < 0) c1 += 26;
            if (c2 < 0) c2 += 26;
            total += std::min(c1, c2) + 1;  // move time + type time
            last = ch;
        }
        return total;
    }
};
