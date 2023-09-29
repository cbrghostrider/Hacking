// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// time complexity O(nm)
// where n = stringSize_
//       m = numWords_
class Solution {
    int numWords_;
    int wordSize_;
    int stringSize_;
    unordered_set<string> dict_;
    unordered_set<int>  wordAt_;
    string compareMe_;  
    
    void initDict_(vector<string>& words) {
        numWords_ = words.size();
        wordSize_ = words[0].size();
        for (int i=0; i<words.size(); i++) {
            dict_.insert(words[i]); //even though you may have duplicates of some word, it is ok 
        }
        sort(words.begin(), words.end());
        for (string& word : words) {
            compareMe_ += word;
        }
    }
    
    void initWordAt_(string s) {
        stringSize_ = s.length();
        for (int i=0; i<s.length(); i++) {
            string str = s.substr(i, wordSize_);
            if (dict_.find(str) != dict_.end()) wordAt_.insert(i);
        }
    }
    
    vector<int> getCandidateIndices_(string& s) {
        vector<int> retval;
        int ALLWORDSIZE = numWords_ * wordSize_;
        for (int i=0; i<stringSize_ - ALLWORDSIZE + 1; i++) {
            bool isCandidate = true;
            vector<string> wordsForSS;
            for (int ctr=0, j=i; ctr<numWords_; ctr++, j+=wordSize_) {
                if (wordAt_.find(j) == wordAt_.end()) {
                    isCandidate = false;
                    break;
                }
                wordsForSS.push_back(s.substr(j, wordSize_));
            }
            
            if (isCandidate) {
                string candidateStr;
                sort(wordsForSS.begin(), wordsForSS.end());
                for (string& str : wordsForSS) {
                    candidateStr += str;
                }
                if (candidateStr == compareMe_) retval.push_back(i);
            }
        }
        return retval;
    }
    

public:
    vector<int> findSubstring(string s, vector<string>& words) {
        initDict_(words);
        initWordAt_(s);
        return getCandidateIndices_(s);
    }
};
