class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        const string digits = "0123456789";      
        int wpos=0, apos=0;
        
        while (wpos < word.size() && apos < abbr.size()) {
            if (digits.find(abbr[apos]) != string::npos) {  // found a digit
                if (abbr[apos] == '0') return false;  // leading zero
                size_t num_end = abbr.find_first_not_of(digits, apos);
                string num_str = abbr.substr(apos, num_end);
                int num = std::stoi(num_str);
                
                if (num + wpos > word.size()) return false;
                wpos += num;
                apos = num_end;
                if (apos == string::npos) {
                    apos = abbr.size();
                    break;
                }
            } else {
                if (abbr[apos++] != word[wpos++]) return false;
            }
        }
        return (wpos == word.size() && apos == abbr.size());
    }
};

