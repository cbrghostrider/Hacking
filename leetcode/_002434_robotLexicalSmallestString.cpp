class Solution {    
    vector<int> counts;
    vector<int> dones;
    void initialize(const string& s) {
        counts = dones = vector<int>(26, 0);
        for (char ch : s) {counts[ch-'a']++;}
    }
public:
    string robotWithString(string s) {
        initialize(s);
        string out, t;
        int s_index = 0;
        for (char ch='a'; ch<='z'; ch++) {
            while (s_index < s.size() && dones[ch-'a'] != counts[ch-'a']) {
                if (!t.empty() && t.back() <= ch) {
                    out.push_back(t.back());                    
                    t.pop_back();
                    continue;
                }
                // Take something from s.
                if (s[s_index] <= ch) {
                    out.push_back(s[s_index]);
                    dones[s[s_index]-'a']++;
                    s_index++;       
                    continue;             
                }
                // Save the thing from s.
                dones[s[s_index]-'a']++;
                t.push_back(s[s_index++]);                
            }
        }
        if (!t.empty()) { 
            std::reverse(t.begin(), t.end()); 
            out += t;
        }
        return out;
    }
};
