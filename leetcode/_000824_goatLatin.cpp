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
public:
    string toGoatLatin(string sentence) {
        string ans;
        LineProcessor lp(sentence);
        int num_a = 1;
        while (lp.hasNext()) {
            string word = lp.next();
            string new_word = (word.size() == 1 ? "" : word.substr(1));
            switch (word[0]) {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                    new_word = string(1, word[0]) + new_word + "ma";
                    break;
                default:
                    new_word += string(1, word[0]) + "ma";
                    break;
            }
            new_word += string(num_a++, 'a');
            ans += new_word;
            if (lp.hasNext()) ans += " ";
        }
        return ans;
    }
};
