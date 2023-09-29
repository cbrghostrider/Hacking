class Solution {
public:
    string truncateSentence(string s, int k) {
        int pos = 0;
        while (k > 0 && pos != string::npos) {
            pos = s.find_first_of(" ", pos);
            k--;
            if (pos == string::npos) break;
            pos++;
        }
        if (pos == string::npos) return s;
        return s.substr(0, --pos);
    }
};
