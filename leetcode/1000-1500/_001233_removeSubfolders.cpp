class Solution {
public:
    // O(n^2) time, O(n) space.
    vector<string> removeSubfolders_On2(vector<string>& folder) {
        std::sort(folder.begin(), folder.end(), [](const string& f1, const string& f2) -> bool {
            if (f1.size() != f2.size()) return f1.size() < f2.size();
            return f1 < f2;
        });
        
        unordered_set<string> chosen;
        for (const string& f : folder) {
            bool choose = true;
            for (const string& c : chosen) {
                if (f.substr(0, c.size()) == c && 
                    f.size() >= c.size()+1 && f[c.size()] == '/') {
                    choose = false;
                    break;
                }
            }
            if (choose) {chosen.insert(f);}
        }
        
        vector<string> ans;
        ans.insert(ans.end(), chosen.begin(), chosen.end());
        return ans;
    }
    
    // O(n*m + nlogn) time, O(n) space.
    vector<string> removeSubfolders(vector<string>& folder) {
        std::sort(folder.begin(), folder.end(), [](const string& f1, const string& f2) -> bool {
            if (f1.size() != f2.size()) return f1.size() < f2.size();
            return f1 < f2;
        });
        
        unordered_set<string> chosen;
        for (const string& f : folder) {
            bool choose = true;
            // break up f into all possible folder prefixes
            for (int i=1; i<f.size(); i++) {
                if (f[i] != '/') continue;
                string str = f.substr(0, i);
                if (chosen.find(str) != chosen.end()) {
                    choose = false;
                    break;
                }
            }
            if (choose) {chosen.insert(f);}
        }
        
        vector<string> ans;
        ans.insert(ans.end(), chosen.begin(), chosen.end());
        return ans;
    }
};
