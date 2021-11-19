class Solution {
    class LineProcessor {
      public:
        LineProcessor(const string& s) : str(s) {
            for (char ch='a'; ch<='z'; ch++) {all_letters.push_back(ch);}
            for (char ch='A'; ch<='Z'; ch++) {all_letters.push_back(ch);}
        }
        bool hasNext() {
            if (s_ptr >= str.size() || s_ptr == string::npos) return false;
            if (str[s_ptr] == ' ')  { s_ptr++; return hasNext();}
            return true;
        }
        string next() {
            if (!hasNext()) {return "";}
            int pos = str.find_first_not_of(all_letters, s_ptr);
            int len = (pos == string::npos ? (str.size()-s_ptr) : (pos-s_ptr));
            string ret = str.substr(s_ptr, len);
            s_ptr = pos;
            return ret;
        }
      private:
        string str;
        string all_letters;
        int s_ptr = 0;
    };
    
    void processSentence(LineProcessor& lp, unordered_map<string, int>& freq) {
        while (lp.hasNext()) {
            string word = lp.next();
            freq[word]++;
        }
    }
    void getUncommons(unordered_map<string, int>& freq1, unordered_map<string, int>& freq2,
                      vector<string>& uncommons) {
        for (const auto& kv : freq1) {
            if (kv.second == 1 && freq2.find(kv.first) == freq2.end()) {
                uncommons.push_back(kv.first);
            }
        }
    }
public:
    // O(n) space, O(n) time.
    vector<string> uncommonFromSentences(string s1, string s2) {
        LineProcessor lp1(s1), lp2(s2);
        unordered_map<string, int> freq1, freq2;
        processSentence(lp1, freq1);
        processSentence(lp2, freq2);
        vector<string> uncommons;
        getUncommons(freq1, freq2, uncommons);
        getUncommons(freq2, freq1, uncommons);
        return uncommons;
    }
};
