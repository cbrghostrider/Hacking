//gets time limit exceeded at the moment
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
    vector<string> getLegitPhrases_(string s, unsigned int start, unsigned int end) {
        vector<string> retval;
        
        //either this entire thing is a word
        if (isWord_[end-start+1-1][start]) {
            string str = s.substr(start, end-start+1);
            retval.push_back(str);
        }
        
        //single letter phrase checked, so no more recursion
        if (start == end) return retval; 
            
        //or it is possibly composed of some sequence of words
        for (unsigned int i=start; i<end; i++) {
            vector<string> lhs = getLegitPhrases_(s, start, i); 
            vector<string> rhs = getLegitPhrases_(s, i+1, end);
            
            if (lhs.empty() || rhs.empty()) continue; //try next combo
            
            for (string& lhsstr : lhs) {
                for (string& rhsstr : rhs) {
                    string thisPhrase = lhsstr + " " + rhsstr;
                    retval.push_back(thisPhrase);
                }
            }
        }
        return retval;
    }

public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        runDynamicProg_(s, wordDict);
        vector<string> retval = getLegitPhrases_(s, 0, s.length()-1);
        freeDynamicProgCache_(s);
        return retval;
    }
};

