// If (val ^ first) == second; then
//    (val ^ first) ^ first == (second ^ first)  ; // apply same operation to both sides
//    val                   == (first ^ second)  ; // x^x == 0 && x ^ 0 == x && commutative property
class Solution {
    string binarize(unsigned int num) {
        string ans;
        unsigned int val=1;
        for (int pos=0; pos<32; pos++) {
            if (val & num) {
                ans.push_back('1');
            } else {
                ans.push_back('0');
            }
            val <<= 1;
        }
        // drop leading zeros
        size_t pos = ans.find_last_of("1");
        if (pos == string::npos) return "0";        
        ans = ans.substr(0, pos+1);
        // printf("Binarize = %s\n", ans.c_str());
        std::reverse(ans.begin(), ans.end());
        return ans;
    }

public:
    // TLE: 54/59 cases passed.
    // Complexity if O(m * n)
    // n == |s|
    // m == |queries|   
    vector<vector<int>> substringXorQueries2(string s, vector<vector<int>>& queries) {
        vector<vector<int>> ans;        
        for (const vector<int>& query : queries) {            
            unsigned int val = (unsigned int)(query[0]) ^ (unsigned int)(query[1]);
            string bin = binarize(val);          

            bool possible = true;
            int found = -1;
            for (int i=0; i<s.size(); i++) {
                possible = true;
                if (i + bin.size() > s.size()) {
                    possible = false;
                    break;
                }                
                for (int pos=i; pos<i+bin.size(); pos++) {
                    if (bin[pos-i] != s[pos]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {    
                    found = i;                
                    break;
                }
            }
            if (possible) {
                ans.push_back({found, found+(int)bin.size()-1});
            } else {
                ans.push_back({-1, -1});
            }
        }
        return ans;
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    // This version is based on precomputation and caching, and is accepted (AC).
    // map from substr in s to position.
    unordered_map<string, int> cache;

    void populateCache(const string& s) {
        for (int sz=1; sz<=30 && sz <=s.size(); sz++) {  // 10^9 fits in 30 digits
            int num=1<<sz;  // num patterns of sz exist
            int done=0;     // these many patterns have been found
            for (int spos=0; spos<=s.size()-sz && done < num; spos++) {
                string sstr = s.substr(spos, sz);
                if (cache.find(sstr) == cache.end()) {
                    cache[sstr] = spos;
                    done++;
                }
            }
        }
    }
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        populateCache(s);        
        vector<vector<int>> ans;        
        for (const vector<int>& query : queries) {            
            unsigned int val = (unsigned int)(query[0]) ^ (unsigned int)(query[1]);
            string bin = binarize(val);          

            if (cache.find(bin) != cache.end()) {
                int found = cache[bin];
                ans.push_back({found, found+(int)bin.size()-1});
            } else {
                ans.push_back({-1, -1});
            }
        }
        return ans;        
    }
};
