// Let nw(i, l) denote the ways a substring of s starting at index i in s and length l
//              matches some substring of t with exactly 1 char difference.
//              (stores indices in t corresponding to this)
//     em(i, l) denote the ways a substring of s starting at index i in s and length l
//              matches some substring of t exactly.
//              (stores indices in t corresponding to this)
// nw(i, l) = 
//    from nw(i+1, l-1) -> 
//           filtered so that the first char s[i] should match the char preceding the "matching" substring from t
//    from em(s[i+1, l-1]) -> 
//           filtered so that first char [si] should NOT match the char preceding the "matching" substring from t

class Solution {
public:
    typedef int Index;
    typedef vector<Index> Choices;
    typedef string Signature;
    
    Signature getSignature(Index i, int len) {
        return (std::to_string(i) + "-" + std::to_string(len));
    }

    // O(n*n*m) time. n = |s|, m = |t|. 
    int countSubstrings(string s, string t) {
        // key = (i, l) pair as described above.
        unordered_map<Signature, Choices> cache_nw;  // value = indices in t for exactly one mismatch
        unordered_map<Signature, Choices> cache_em;  // value = indices in t for exact match
        
        // Prepopulate cache.
        for (int si=0; si<s.size(); si++) {
            Signature sig = getSignature(si, 1);
            for (int ti=0; ti<t.size(); ti++) {
                if (s[si] == t[ti]) {
                    cache_em[sig].push_back(ti);
                } else {
                    cache_nw[sig].push_back(ti);
                }
            }
        }
        
        for (int si=s.size()-1; si>=0; si--) {
            for (int l=2; l<=s.size()-si; l++) {
                Signature sig = getSignature(si, l);
                
                // Rest of the word has exactly 1 mismatch
                for (Index ti : cache_nw[getSignature(si+1, l-1)]) {
                    if (ti == 0 || t[ti-1] != s[si]) continue;
                    // And curr character matches.
                    cache_nw[sig].push_back(ti-1);
                }
                
                // Rest of the word matches.
                for (Index ti : cache_em[getSignature(si+1, l-1)]) {
                    if (ti == 0) continue;
                    if (t[ti-1] == s[si]) {
                        // And curr char also matches.
                        cache_em[sig].push_back(ti-1);
                    } else {
                        // And curr char does not match.
                        cache_nw[sig].push_back(ti-1);
                    }
                }
            }
        }
        
        int count=0;
        for (const auto& kv : cache_nw) {
            count += kv.second.size();
        }
        return count;
    }
};
