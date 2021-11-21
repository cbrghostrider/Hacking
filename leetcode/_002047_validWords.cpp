class Solution {
    bool isValid(const string& s, int start, int end) {
        int hyphen_pos=-1, punc_pos=-1;
        for (int i=start; i<=end; i++) {
            if (s[i] >= 'a' && s[i] <= 'z') continue;
            if (s[i] >= '0' && s[i] <= '9') return false;
            if (s[i] == '-') {
                if (hyphen_pos != -1) return false;
                hyphen_pos = i;
                continue;
            }
            if (punc_pos != -1) return false;
            punc_pos = i;
        }
        if (!(punc_pos == -1 || punc_pos == end)) return false;
        if (hyphen_pos != -1) {
            if (hyphen_pos == start || hyphen_pos == end) return false;
            if (end-start+1 < 3) return false;
            char b = s[hyphen_pos-1], a = s[hyphen_pos+1];
            if (!(b >= 'a' && b <='z')) return false;
            if (!(a >= 'a' && a <='z')) return false;
        }
        return true;
    }
public:
    int countValidWords(string sentence) {
        int s_ptr=0, count=0;
        while (s_ptr < sentence.size() && s_ptr != string::npos) {
            int pos_s = sentence.find_first_not_of(" ", s_ptr);
            if (pos_s == string::npos) break;
            int pos_e = sentence.find_first_of(" ", pos_s);
            pos_e = (pos_e == string::npos ? sentence.size()-1 : pos_e-1);
            if (isValid(sentence, pos_s, pos_e)) { 
                count++; 
            }
            s_ptr = pos_e + 1;
        }
        return count;
    }
};
