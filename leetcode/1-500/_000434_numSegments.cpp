class Solution {
public:
    int countSegments(string s) {
        bool in_word = false;
        int count=0;
        for (char ch : s) {
            if (ch == ' ') {
                in_word = false;
            } else {
                if (!in_word) count++;
                in_word = true;
            }
        }
        return count;
    }
};
