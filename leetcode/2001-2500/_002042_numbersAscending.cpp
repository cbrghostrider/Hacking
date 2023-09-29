class Solution {
public:
    bool areNumbersAscending(string s) {
        int last=-1, s_ptr=0;
        while (s_ptr < s.size() && s_ptr != string::npos) {
            int pos_s = s.find_first_of("0123456789", s_ptr);
            if (pos_s == string::npos) break;
            int pos_e = s.find_first_not_of("0123456789", pos_s);
            int len = (pos_e == string::npos ? s.size()-pos_s : pos_e-pos_s);
            int num = std::stoi(s.substr(pos_s, len));
            if (num <= last) return false;
            last = num;
            s_ptr = pos_e;
        }
        return true;
    }
};
