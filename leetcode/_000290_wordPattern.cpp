class Solution {
    class StringProcessor {
      public:
        StringProcessor(const string& s) : str(s), s_ptr(0) {}
        bool hasNext() {
            if (s_ptr >= str.size() || s_ptr == string::npos) return false;
            if (str[s_ptr] == ' ') { s_ptr++; return true;}
            return true;
        }   
        string next() {
            if (!hasNext()) return "";
            int n_ptr = str.find_first_of(" ", s_ptr);
            string ret = str.substr(s_ptr, (n_ptr == string::npos ? n_ptr : n_ptr - s_ptr));
            s_ptr = (n_ptr == string::npos ? n_ptr : n_ptr + 1);
            return ret;
        }
        
      private:
        const string str;
        int s_ptr = 0;
    };
public:
    // O(n) time, O(1) space.
    bool wordPattern(string pattern, string s) {
        StringProcessor sp(s);
        unordered_map<char, string> word_map;
        unordered_map<string, char> reverse_word_map;
        int p_ptr = 0;
        while (p_ptr < pattern.size() && sp.hasNext()) {
            string word = sp.next();
            char ch = pattern[p_ptr++];
            auto witer = word_map.find(ch);
            auto riter = reverse_word_map.find(word);
            
            if (witer == word_map.end() && riter == reverse_word_map.end()) {
                word_map[ch] = word;
                reverse_word_map[word] = ch;
            } else if (witer != word_map.end() && witer->second != word) {
                return false;
            } else if (riter != reverse_word_map.end() && riter->second != ch) {
                return false;
            }
        }
        return (p_ptr >= pattern.size() && !sp.hasNext());
    }
};
