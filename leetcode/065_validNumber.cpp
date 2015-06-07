// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// OMFG! Mother of all edge cases...
//
class Solution {
    bool isInteger(string n) {
        if (n == "") return false;
        auto pos = n.find_first_not_of("0123456789");
        return (pos == string::npos);
    }
    bool isForm(string sp, string s, bool integralFirst = true) {
        auto sz = s.find_first_of(sp);
        if (sz == string::npos) return false;
        string before = s.substr(0, sz);
        string after  = s.substr(sz+1);
        bool decFirst = isDecForm(before);
        bool intFirst = isInteger(before);
        return ( (integralFirst ? (intFirst) : (decFirst || intFirst)) && isInteger(after));
    }
    bool simplifyExp(string& s, string sp) {
        auto pos = s.find(sp);
        if (pos != string::npos) {
            s = s.substr(0, pos) + "e" + s.substr(pos+sp.length());
        }
    }
    bool isExpForm(string s) {
        if (s == "e" || s == "E") return false;
        simplifyExp(s, ".E");
        simplifyExp(s, ".e");
        simplifyExp(s, "e+");
        simplifyExp(s, "e-");
        return (isForm("eE", s, false));
    }
    bool isDecForm(string s) {
        if (s == ".") return false;
        if (s.length() > 1 && s[0] == '.') return isInteger(s.substr(1));
        if (s.length() > 1 && s[s.length()-1] == '.') {
            s.pop_back();
            return isInteger(s);
        }
        return (isForm(".", s));
    }
    bool isSignStart(string s) {
        if (s.length() > 1 && (s[0] == '-' || s[0] == '+')) {
            return isNumberPrime(s.substr(1));
        }
        return false;
    }
    void eatLeadTrailSpaces(string& s) {
        auto spos = s.find_first_not_of(" ");
        auto epos = s.find_last_not_of(" ");
        if (spos == string::npos) {
            s = "";
            return;
        }
        s = s.substr(spos, epos-spos+1);
    }
    bool isNumberPrime(string s) {
        return (isInteger(s) || isExpForm(s) || isDecForm(s) || isSignStart(s));
    }
public:
    bool isNumber(string s) {
        eatLeadTrailSpaces(s);
        if (s == "") return false;
        if (s.find("..") != string::npos) return false;
        if (s.find("+-") != string::npos) return false;
        if (s.find("-+") != string::npos) return false;
        if (s.find("++") != string::npos) return false;
        if (s.find("--") != string::npos) return false;
        return isNumberPrime(s);
    }
};
