//simpler dynamic programming solution, using only 1-D array

class Solution {
private:
    bool *isWord_; 
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        //allocate cache
        isWord_ = new bool[s.length()];
        
        //base case- is [0, 0] a word?
        isWord_[0] = (wordDict.find(s.substr(0, 1)) == wordDict.end()) ? false : true;
        
        //main dynamic programming algorithm
        for (unsigned int i=1; i<s.length(); i++) { 
                // is [0,i] one huge word?
                bool isWord = (wordDict.find(s.substr(0, i+1)) == wordDict.end()) ? false : true;
                
                for (unsigned int j=0; j<i; j++) {
                    //if [0, j] is a bunch of words, and [j+1, i] is a word, we are good!
                    bool isWord_jp1_i = (wordDict.find(s.substr(j+1, i-j)) == wordDict.end()) ? false : true;
                    if (isWord_[j] && isWord_jp1_i) {
                        isWord = true;
                        break;
                    }
                }
                
                //Is phrase starting from the beginning, and ending at i a word or collection of words?
                isWord_[i] = isWord;
        }
        bool retval = isWord_[s.length()-1];
        delete [] isWord_;
        return retval;
    }
};
