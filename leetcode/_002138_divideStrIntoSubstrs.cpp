class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        if (s.empty() || k <= 0) return {};
        if (s.size() % k != 0) {
            s = s + string(k - (s.size() % k), fill);
        }

        vector<string> ans;
        int pos=0;
        while (pos < s.size() && pos != string::npos) {
            ans.push_back(s.substr(pos, k));
            pos += k;
        }
        return ans;
    }
};