class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int s_ptr=0;
        int index = 0;
        while (s_ptr < sentence.size() && s_ptr != string::npos) {
            size_t pos_s = sentence.find_first_not_of(" ", s_ptr);
            if (pos_s == string::npos) { return -1; }
            size_t pos_e = sentence.find_first_of(" ", pos_s);
            int len = (pos_e == string::npos ? sentence.size()-pos_s: pos_e-pos_s);
            string word = sentence.substr(pos_s, len);
            s_ptr = pos_e;
            index++;
            if (searchWord.size() <= word.size() && searchWord == word.substr(0, searchWord.size())) {
                return index;
            }
        }
        return -1;
    }
};
