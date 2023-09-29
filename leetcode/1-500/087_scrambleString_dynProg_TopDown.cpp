// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// This was a very interesting problem! Here is my solution, using top down dynamic programming. 
//
// Lets discuss the recurrence. The question posed is, when is string s1 considered to be a scrambling of string s2? 
// Let us pose this as a modified question in the form of the following boolean function:
// bool isScrambling(int s1s, int s1e, int s2s, int s2e);
// i.e., given two strings s1 and s2, are their SUBSTRINGS s1[s1s, s1e] and s2[s2s, s2e] scramblings of each other?
// The original question can be answered by isScrambling(0, s1.length()-1, 0, s2.length() -1);
//
//    First the trivial cases which result in false result:
//     1. The two strings are not of same length, then it cannot be a scrambling.
//     2. if s1e < s1s, or s2e < s2s, then they are not scramblings of each other.
//
//    Now the case for identity scrambling (i.e. no scrambling at all)
//    If s1[s1s, s1e] == s2[s2s, s2e] then they are trivial scramblings of each other
//
//    Another trivial case, if the two strings are of length 1, just check that character
//    
//    Now we come to the meat of the problem. Consider all breaks of the string s1:
//    s1[s1s, s1s+k] and s1[s1s+k+1, s1e] for all k <-[0..(s1e-s1s)]
//       for each of these substrings, the original strings are scramblings if
//       1. Either isScrambling(s1s, s1s+k, s2s, s2s+k)   && isScrambling(s1s+k+1, s1e, s2s+k+1, s2e)
//       2. Or isScrambling(s1s, s1s+k, (s2e-k), s2e)     && isScrambling(s1s+k+1, s1e, s2s, s2e-k-1)
//     The first case is one where we do NOT flip the current node in the tree.
//     The second case is one where we flip the current node in the tree.
//
//    If none of the above cases return true, then the strings are NOT scramblings of each other.
//
// Here is a non-memoized (hence non-DP) recursive version:
class Solution {
    string s1;
    string s2;
public:
    // is s1[s1s, s1e] a scrambling of s2[s2s, s2e]?
    bool isScrambling (int s1s, int s1e, int s2s, int s2e) {
        if ((s1e-s1s) != (s2e-s2s)) return false;
        if (s1e < s1s || s2e < s2s) return false;
        if (s1.substr(s1s, (s1e - s1s + 1)) == s2.substr(s2s, (s2e - s2s + 1))) return true; //identity scrambling
        if (s1e == s1s) return s1[s1s] == s2[s2s];     
        for (int k=0; k<(s1e-s1s); k++) { 
            if (isScrambling(s1s, s1s+k, s2s, s2s+k)   && isScrambling(s1s+k+1, s1e, s2s+k+1, s2e)) return true;
            if (isScrambling(s1s, s1s+k, (s2e-k), s2e) && isScrambling(s1s+k+1, s1e, s2s, s2e-k-1)) return true;
        }
        return false;
    }
    bool isScramble(string is1, string is2) {
        if (is1.length() == 0 || is2.length() == 0) return false;
        s1 = is1;
        s2 = is2;
        return isScrambling(0, s1.length()-1, 0, s2.length()-1);
    }
};
// The above solution is functionally correct, but will result in Time-Limit-Exceeded, 
// because we are solving the same sub-problems again and again and again
//
// To make this dynamic programming, we just have to memoize the results. 
// i.e. first check if results are in the cache, if so return them
// else compute the results, store in cache, and return the result.
// Here is a Top-Down dynamic programming version, which now passes in the online judge:
//
class Solution {
    string s1;
    string s2;
    std::hash<std::string> str_hash;
    unordered_map<size_t, bool> cache;
    
    // is s1[s1s, s1e] a scrambling of s2[s2s, s2e]?
    bool isScrambling (int s1s, int s1e, int s2s, int s2e) {
        string hashStr = s1.substr(s1s, s1e-s1s+1) + "#" + s2.substr(s2s, s2e-s2s+1);
        auto it = cache.find(str_hash(hashStr));
        if (it != cache.end()) { 
            return it->second;
        }
        bool ret = false;
        if ((s1e-s1s) != (s2e-s2s)) {ret = false;}
        else if (s1e < s1s || s2e < s2s) {ret = false;}
        else if (s1.substr(s1s, (s1e - s1s + 1)) == s2.substr(s2s, (s2e - s2s + 1)))  { ret = true;} //identity scrambling
        else if (s1e == s1s) {ret = s1[s1s] == s2[s2s];}      
        else {
            for (int k=0; k<(s1e-s1s); k++) { 
                if (isScrambling(s1s, s1s+k, s2s, s2s+k)   && isScrambling(s1s+k+1, s1e, s2s+k+1, s2e)) {ret = true; break;}
                if (isScrambling(s1s, s1s+k, (s2e-k), s2e) && isScrambling(s1s+k+1, s1e, s2s, s2e-k-1)) {ret = true; break;}
            }
        }
        cache[str_hash(hashStr)] = ret;
        return ret;
    }
public:
    bool isScramble(string is1, string is2) {
        if (is1.length() == 0 || is2.length() == 0) return false;
        s1 = is1;
        s2 = is2;
        return isScrambling(0, s1.length()-1, 0, s2.length()-1);
    }
};
