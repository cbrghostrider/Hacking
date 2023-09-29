class Solution {
public:
    string reorderSpaces(string text) {
        if (text.empty()) return "";
        int count_spaces=0, s_ptr=0;
        
        if (text[0] == ' ') {
            int pos = text.find_first_not_of(" ", s_ptr);
            if (pos == string::npos) return text;
            count_spaces += pos;
            s_ptr = pos;
        }
        
        vector<string> words;
        while (s_ptr < text.size() && s_ptr != string::npos) {
            int pos = text.find_first_of(" ", s_ptr);
            int len = (pos == string::npos ? text.size()-s_ptr : pos-s_ptr);
            words.push_back(text.substr(s_ptr, len));
            if (pos == string::npos) {break;}
            s_ptr = pos;
            
            pos = text.find_first_not_of(" ", s_ptr);
            len = (pos == string::npos ? text.size()-s_ptr : pos-s_ptr);
            count_spaces += len;
            
            s_ptr = pos;
        }
        
        int quot = (words.size() == 1 ? 0 : count_spaces / (words.size()-1));
        int rem = (words.size() == 1 ? count_spaces : count_spaces % (words.size()-1));
        
        string ans;
        for (int i=0; i<words.size()-1; i++) {
            ans += words[i] + std::string(quot, ' ');
        }
        ans += words.back() + std::string(rem, ' ');
        return ans;
    }
};
