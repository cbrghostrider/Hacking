class Solution {
    int longestCont(const string& s, char ch) {
        int s_ptr=0, longest=0;
        while (s_ptr < s.size() && s_ptr != string::npos) {
            int pos_s = s.find_first_of(std::string(1, ch), s_ptr);
            if (pos_s == string::npos) {break;}
            int pos_e = s.find_first_not_of(std::string(1, ch), pos_s);
            int len = (pos_e == string::npos ? s.size()-pos_s : pos_e-pos_s);
            if (longest < len) {longest=len;}
            s_ptr = pos_e;
        }
        return longest;
    }
public:
    bool checkZeroOnes(string s) {
        return (longestCont(s, '1') > longestCont(s, '0'));
    }
};
