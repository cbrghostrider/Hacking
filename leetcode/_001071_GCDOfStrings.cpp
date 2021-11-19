class Solution {
    // Checks if a string of size n (starting at 0), divides string s.
    bool checkIfDivides(const string& s, int n) {
        if (n<=0 || n > s.size()) return false;
        if (s.size() % n) return false;
        string ss = s.substr(0, n);
        for (int i=0; i<s.size(); i+=n) {
            if (ss != s.substr(i, n)) return false;
        }
        return true;
    }
public:
    string gcdOfStrings(string str1, string str2) {
        if (str1.size() == 0 || str2.size() == 0) return "";
        int limit = std::min(str1.size(), str2.size());
        for (int n=limit; n>=1; n--) {
            if ((str1.size() % n) || (str2.size() % n)) continue;
            if (!checkIfDivides(str1, n)) continue;
            if (!checkIfDivides(str2, n)) continue;
            if (str1.substr(0, n) != str2.substr(0, n)) continue;
            return str1.substr(0, n);
        }
        return "";
    }
};
