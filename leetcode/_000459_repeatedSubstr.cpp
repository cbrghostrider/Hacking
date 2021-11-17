class Solution {
    bool isRepeatSize(const string& s, int size) {
        if (size <=0 || size >s.size()/2) return false;
        if (s.size() % size != 0) return false;
        string test = s.substr(0, size);
        for (int i=0; i<s.size(); i+=size) {
            string istr = s.substr(i, size);
            if (istr != test) return false;
        }
        return true;
    }
    
public:
    bool repeatedSubstringPattern(string s) {
        for (int i=s.size()/2; i>=0; i--) {
            if (isRepeatSize(s, i)) return true;
        }
        return false;
    }
};
