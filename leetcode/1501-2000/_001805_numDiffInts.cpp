class Solution {
    string removeLeadingZeros(const string& s) {
        int s_ptr = 0;
        while (s_ptr < s.size() && s[s_ptr] == '0') {s_ptr++;}
        if (s_ptr == s.size()) return "0";
        return s.substr(s_ptr);
    }
public:
    int numDifferentIntegers(string word) {
        for (char& ch : word) {if (!(ch >= '0' && ch <= '9')) {ch = ' ';}}
        unordered_set<string> nums;
        int s_ptr=0;
        while (s_ptr < word.size() && s_ptr != string::npos) {
            int pos_s = word.find_first_of("0123456789", s_ptr);
            if (pos_s == string::npos) break;
            int pos_e = word.find_first_not_of("0123456789", pos_s);
            int len = (pos_e == string::npos ? word.size()-pos_s : pos_e-pos_s);
            nums.insert(removeLeadingZeros(word.substr(pos_s, len)));
            s_ptr = pos_e;
        }
        return nums.size();
    }
};
