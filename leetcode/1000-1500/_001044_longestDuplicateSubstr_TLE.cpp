class Solution {
    
    // key_1: i
    // key_2: j
    // key_3: size
    // value: true/false
    // is s[i, i+sz-1] == s[j, j+sz-1]
    unordered_map<int, unordered_map<int, unordered_map<int, bool>>> dup_cache;
    
    bool isIdentical(const string& s, int i, int j, int sz) {
        if (i+sz-1 >= s.size() || j+sz-1 >= s.size()) return false;
        
        if (dup_cache[i][j].find(sz) != dup_cache[i][j].end()) {
            return dup_cache[i][j][sz];
        }
        
        if (sz == 1) {
            dup_cache[i][j][sz] = s[i] == s[j];
            return dup_cache[i][j][sz];
        }
        
        bool ret = s[i] == s[j] && isIdentical(s, i+1, j+1, sz-1);
        dup_cache[i][j][sz] = ret;
        return ret;
    }
    
    // empty string is "false"
    unordered_map<int, string> cache;
    
    string dupLenN(const string& s, int N) {
        if (cache.find(N) != cache.end()) { return cache[N]; }
        
        string ret;
        for (int i=0; i+N-1 < s.size(); i++) {
            for (int j=i+1; j+N-1 < s.size(); j++) {
                if (isIdentical(s, i, j, N)) {
                    ret = s.substr(i, N);
                    break;
                }
            }
            if (!ret.empty()) break;
        }
        
        cache[N] = ret;
        return ret;
    }
    
    
    string getBest(const string& s, int lo, int hi) {
        if (lo == hi) return cache[lo];
        if (lo+1 == hi) {
            string hi_str = dupLenN(s, hi);
            if (!hi_str.empty()) return hi_str;
            else return dupLenN(s, lo);
        }
        int mid = (lo+hi)/2;
        if (!dupLenN(s, mid).empty()) {
            return getBest(s, mid, hi);
        }
        return getBest(s, lo, mid);
    }
    
    
public:
    string longestDupSubstring(string s) {
        cache[s.size()] = "";
        cache[0] = "<SPECIAL>";
        
        string best = getBest(s, 0, s.size());
        if (best == cache[0]) return "";
        return best;
    }
};
