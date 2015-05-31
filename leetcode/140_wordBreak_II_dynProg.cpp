class Solution {
private:
    vector<vector<int> > phrases_; 
    vector<string> constructRetval(const string& s, int ind) {
        if (ind < 0 ) return vector<string>(1, ""); 
        vector<string> retval;
        for (const int& start : phrases_[ind]) {
            vector<string> recurse = constructRetval(s, start-1);
            for (string ph : recurse) {
                string myword = s.substr(start, ind-start+1);
                ph = (ph == "") ? myword : ph + " " + myword;
                retval.push_back(ph);
            }
        }
        return retval;
    }
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        //allocate cache
        for (unsigned int i=0; i<s.size(); i++) {
            vector<int> cache; //start indices for word ending at my index
            phrases_.push_back(cache);
        }
        
        //main dynamic programming algorithm
        for (unsigned int i=0; i<s.length(); i++) { 
            // is [0,i] one huge word?
            string testWholeWord = s.substr(0, i+1);
            if (wordDict.find(testWholeWord) != wordDict.end()) {
                phrases_[i].push_back(0);
            }
                
            for (unsigned int j=0; j<i; j++) {
                //if [0, j] is a bunch of words, and [j+1, i] is a word, we are good!
                string testMe = s.substr(j+1, i-j);
                if ((wordDict.find(testMe) != wordDict.end()) && !phrases_[j].empty()) {
                    phrases_[i].push_back(j+1);
                }
            }
        }
        return constructRetval(s, s.length()-1);
    }
};
