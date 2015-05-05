//Too complicated, because it uses a 2-D array
//Time-Limit-Exceeded
//Other solution is simpler!
class Solution {
private:
    bool **isWord_;
    void runDynamicProg_(string s, unordered_set<string>& wordDict) {
        //allocate cache
        isWord_ = new bool*[s.length()];
        for (unsigned int i=0; i<s.length(); i++) {
            isWord_[i] = new bool[s.length()];
        }
        
        //main dyn programming algorithm
        for (unsigned int sz=1; sz <= s.length(); sz++) {
            unsigned int szInd = sz-1;
            for (unsigned int i=0; i<s.length() && (i+sz-1)<s.length(); i++) { //i denotes starting index
                string testMe = s.substr(i, sz);
                
                //Is word of size sz starting at index i in s, a legit word or not?
                isWord_[szInd][i] = (wordDict.find(testMe) == wordDict.end()) ? false : true;
            }
        }
    }
    
    void freeDynamicProgCache_(string s) {
        for (unsigned int i=0; i<s.length(); i++) {
            delete [] isWord_[i];
        }
        delete [] isWord_;
    }
    
    //do letters between [start, end] inclusive, form a legit phrase
    bool isLegitPhrase_(unsigned int start, unsigned int end) {
        
        //either this entire thing is a word
        if (isWord_[end-start+1-1][start]) return true;
        
        //single letter phrase didn't exist, so no more recursion
        if (start == end) return false; 
            
        //or it is possibly composed of some sequence of words
        for (unsigned int i=start; i<end; i++) {
            if (isLegitPhrase_(start, i) && isLegitPhrase_(i+1, end)) return true;
        }
        
        //no dice... not a legit phrase
        return false;
    }

public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        runDynamicProg_(s, wordDict);
        bool retval = isLegitPhrase_(0, s.length()-1);
        freeDynamicProgCache_(s);
        return retval;
    }
};
