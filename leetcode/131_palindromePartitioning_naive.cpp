//gets time limit exceeded. Other solution works.
class Solution {
    typedef vector<vector<string>> PalPart;
    unordered_map<string, PalPart> cache;
    
    bool isPalindrome_(const string& s) {
        for (int i=0; i<s.length()/2; i++) {
            if (s[i] != s[s.length()-1-i]) return false;
        }
        return true;
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> retval;
        if (s.length() == 0) return retval;
        
        //check cache
        auto it = cache.find(s);
        if (it != cache.end()) {
            return it->second;
        }
        
        if (isPalindrome_(s)) {
            vector<string> ret(1, s);
            retval.push_back(ret);
        }
        
        //recursion base case
        if (s.length() == 1) {
            cache[s] = retval;
            return retval;
        }
        
        //partition s
        for (int p=1; p<s.size()-1; p++) {
            PalPart pL = partition(s.substr(0, p));
            PalPart pR = partition(s.substr(p));
            
            for (vector<string>& pl : pL) {
                for (vector<string>& pr : pR) {
                    vector<string> ret = pl; 
                    ret.insert(ret.end(), pr.begin(), pr.end());
                    retval.push_back(ret);
                }
            }
        }
        
        //populate cache
        cache[s] = retval;
        return retval;
    }
};
