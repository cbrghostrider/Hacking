class Solution {
    
    // Note that odd letters can never be in even positions, and vice versa.
    // Also all even letters can be rearraged among themselves willy-nilly (and so for odd).
    // The key insight is, if the following conditions hold for s1, s2, then they are special equiv:
    // 1. Same number of same letters in evens group. [comparing s1 and s2]
    // 2. Same number of same letters in odds group. [comparing s1 and s2]
    //
    // So if we take all the odd letters, create a string, and sort it,
    // then we take all the even letters, create a string, and sort it
    // then put back all the odd letters and even letters in order
    // it will create a unique signature for that special equivalent group
    
    string getSignature(const string& str) {
        string odds, evens;
        for (int i=0; i<str.size(); i++) {
            if (i%2 == 0) { evens.push_back(str[i]); } else { odds.push_back(str[i]); }
        }
        std::sort(evens.begin(), evens.end());
        std::sort(odds.begin(), odds.end());
        string sig;
        for (int i=0, o=0, e=0; i<str.size(); i++) {
            if (i%2 == 0) { sig.push_back(evens[e++]); } else { sig.push_back(odds[o++]); }
        }
        return sig;
    }
public:
    int numSpecialEquivGroups(vector<string>& words) {
        unordered_map<string, int> sig_count;
        for (const string& word: words) {
            sig_count[getSignature(word)]++;
        }
        return sig_count.size();
    }
};
