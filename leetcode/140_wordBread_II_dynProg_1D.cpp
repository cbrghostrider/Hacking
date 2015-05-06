//this one gets memory limit exceeded at the moment
class Solution {
private:
    vector<vector<string> > phrases_; 
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        //allocate cache
        for (unsigned int i=0; i<s.size(); i++) {
            vector<string> cache;
            phrases_.push_back(cache);
        }
        
        //base case- is [0, 0] a word?
        if (wordDict.find(s.substr(0, 1)) != wordDict.end()) {
            phrases_[0].push_back(s.substr(0, 1));
        }
        
        //main dynamic programming algorithm
        for (unsigned int i=1; i<s.length(); i++) { 
            // is [0,i] one huge word?
            string testWholeWord = s.substr(0, i+1);
            if (wordDict.find(testWholeWord) != wordDict.end()) {
                phrases_[i].push_back(testWholeWord);
            }
                
            for (unsigned int j=0; j<i; j++) {
                //if [0, j] is a bunch of words, and [j+1, i] is a word, we are good!
                const vector<string>& bunchOfWords = phrases_[j];
                string testMe = s.substr(j+1, i-j);
                if ((wordDict.find(testMe) != wordDict.end()) && !bunchOfWords.empty()) {
                    for (const string& strlhs : bunchOfWords) {
                        string newStr = strlhs + " " + testMe;
                        phrases_[i].push_back(newStr);
                    }
                }
            }
        }
        return phrases_[s.length()-1];
    }
};
