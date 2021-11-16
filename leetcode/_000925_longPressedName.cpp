class Solution {
    // returns length of end of string of chars starting at ptr
    int getEndOfChars(const string& name, char c, int ptr) {
        int len=0;
        while (ptr < name.size() && name[ptr] == c) {
            len++;
            ptr++;
        }
        return len;
    }
public:
    bool isLongPressedName(string name, string typed) {
        int n_ptr=0, t_ptr=0;
        while (n_ptr < name.size() && t_ptr < typed.size()) {
            if (name[n_ptr] != typed[t_ptr]) return false;
            
            int n_len = getEndOfChars(name, name[n_ptr], n_ptr);
            int t_len = getEndOfChars(typed, typed[t_ptr], t_ptr);
            if (n_len > t_len) return false;
            n_ptr += n_len;
            t_ptr += t_len;
        }
        return (n_ptr == name.size() && t_ptr == typed.size());
    }
};
