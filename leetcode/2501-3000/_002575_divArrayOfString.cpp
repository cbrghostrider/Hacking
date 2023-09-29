class Solution {
public:
    vector<int> divisibilityArray(string word, int m) {
        vector<int> ans;
        long long rem=0;
        for (char ch : word) {
            int chint = std::stoi(string(1, ch));
            rem *= 10;
            rem += chint;
            rem = rem % m;
            int n = (rem == 0) ? 1 : 0;
            ans.push_back(n);            
        }
        return ans;
    }
};
