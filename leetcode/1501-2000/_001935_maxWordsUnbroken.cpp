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
            s_ptr = pos;
            return ret;
        }
      private:
        string str;
        string all_letters;
        int s_ptr = 0;
    };
public:
    int canBeTypedWords(string text, string brokenLetters) {
        int count=0;
        LineProcessor lp(text);
        while (lp.hasNext()) {
            string word = lp.next();
            if (word.find_first_of(brokenLetters) == string::npos) count++;
        }
        return count;
    }
};
