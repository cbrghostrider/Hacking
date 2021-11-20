class Solution {
    bool isNice(const string& s, int start, int end) {
        unordered_set<char> lowers, uppers;
        for (int i=start; i<=end;i++) {
            char ch = s[i];
            if (ch >= 'a' && ch <= 'z') {lowers.insert(ch);} else {uppers.insert(ch);}
        }
        for (int i=start; i<=end;i++) {
            if (uppers.find(toupper(s[i])) == uppers.end()) {return false;}
        }
        for (int i=start; i<=end;i++) {
            if (lowers.find(tolower(s[i])) == lowers.end()) {return false;}
        }
        return true;
    }
public:
    string longestNiceSubstring(string str) {
        int len=-1;
        int start=-1, end=-1;
        for (int s=0; s<str.size(); s++) {
            for (int e=s; e<str.size(); e++) {
                if (isNice(str, s, e)) {
                    int l = e-s+1;
                    if (l > len) {
                        len=l; start=s; end=e;
                    }
                }
            }
        }
        if (len == -1) return "";
        return str.substr(start, end-start+1);
    }
};
