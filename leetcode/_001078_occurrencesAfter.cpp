class Solution {
    class LineProcessor {
      public:
        LineProcessor(const string& s) : str(s) {
            for (char ch='a'; ch<='z'; ch++) { all_letters.push_back(ch); }
        }
        // returns whether the line has more words to provide.
        bool hasNext() {
            if (s_ptr >= str.size() || s_ptr == string::npos) return false;
            if (str[s_ptr] == ' ') {s_ptr++; return hasNext();}
            return true;
        }
        // provides the next word, if exists.
        string next() {
            if (!hasNext()) return "";
            int pos = str.find_first_not_of(all_letters, s_ptr);
            int len = (pos == string::npos ? str.size()-s_ptr : pos-s_ptr);
            string ret = str.substr(s_ptr, len);
            word_locs.push_back(s_ptr);
            s_ptr = pos;
            return ret;
        }
        // rewinds line so we move back 1 word, if possible.
        void rewind() {
            if (word_locs.empty()) return;
            s_ptr = word_locs.back();
            word_locs.pop_back();
        }
      private:
        string str;
        string all_letters;
        int s_ptr = 0;
        vector<int> word_locs;
    };
public:
    // O(n) time: Since we won't process each word more than 3 times (as w1, w2, w3).
    // O(n) space: Since the rewind vector can take n integers.
    vector<string> findOcurrences(string text, string first, string second) {
        vector<string> ans;
        LineProcessor lp(text);
        while (lp.hasNext()) {
            string w1 = lp.next();
            string w2, w3;
            if (!lp.hasNext()) break;
            w2 = lp.next();
            if (!lp.hasNext()) break;
            w3 = lp.next();
            if (w1 == first && w2 == second) {ans.push_back(w3);}
            lp.rewind();  // put back w3
            lp.rewind();  // put back w2
        }
        return ans;
    }
};
