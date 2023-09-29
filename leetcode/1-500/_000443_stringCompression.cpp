class Solution {
public:
    int compress(vector<char>& chars) {
        int chars_end_plus1 = chars.size();
        int s_ptr=0, w_ptr=0;
        while (s_ptr < chars_end_plus1) {
            int e_ptr = s_ptr;
            while (e_ptr < chars_end_plus1 && chars[s_ptr] == chars[e_ptr]) {e_ptr++;}
            int len = e_ptr - s_ptr;
            string len_str;
            if (len > 1) {len_str = std::to_string(len);}
            chars[w_ptr++] = chars[s_ptr];
            for (char ch : len_str) { chars[w_ptr++] = ch; }
            s_ptr = e_ptr;
        }
        chars.erase(std::begin(chars)+w_ptr, chars.end());
        return chars.size();
    }
};
