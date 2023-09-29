class Solution {
public:
    // O(nlogn) time, O(n) space.
    string sortString(string s) {
        unordered_map<char, int> freqs;
        string uniques;
        
        for (char ch : s) {
            if (freqs.find(ch) == freqs.end()) { uniques.push_back(ch);}
            freqs[ch]++;
        }
        std::sort(uniques.begin(), uniques.end());
        
        int leftover = s.size();
        string ans;
        while (leftover > 0) {
            for (int i=0; i<uniques.size() && leftover > 0; i++) {
                char ch = uniques[i];
                if (freqs[ch] > 0) {
                    ans.push_back(ch);
                    freqs[ch]--;
                    leftover--;
                }
            } 
            for (int i=uniques.size()-1; i>=0 && leftover > 0; i--) {
                char ch = uniques[i];
                if (freqs[ch] > 0) {
                    ans.push_back(ch);
                    freqs[ch]--;
                    leftover--;
                }
            }
        }
        return ans;
    }
};
