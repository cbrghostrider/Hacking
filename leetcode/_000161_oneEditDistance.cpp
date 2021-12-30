class Solution {
    
    bool isOneEditUnequalSizes(const string& bigger, const string& smaller) {        
        for (int i=0; i<bigger.size(); i++) {
            string ss = i == 0 ? "" : bigger.substr(0, i);
            ss += (i == bigger.size()-1) ? "" : bigger.substr(i+1);
            if (ss == smaller) return true;
        }
        return false;
    }
    
    bool isOneEditEqualSizes(const string& s1, const string& s2) {        
        if (s1 == s2) return false;
        for (int i=0; i<s1.size(); i++) {  // s1 and s2 equal sizes, so can index together
            string ms1 = s1; ms1[i] = '.';
            string ms2 = s2; ms2[i] = '.';
            if (ms1 == ms2) return true;
        }
        return false;
    }
public:
    bool isOneEditDistance(string s, string t) {
        bool s_bigger_1 = s.size() == t.size()+1;
        bool t_bigger_1 = t.size() == s.size()+1;
        bool equal_sizes = t.size() == s.size();
        
        if (!(s_bigger_1 || t_bigger_1 || equal_sizes)) return false;
        if (s_bigger_1) return isOneEditUnequalSizes(s, t);
        if (t_bigger_1) return isOneEditUnequalSizes(t, s);
        return isOneEditEqualSizes(s, t);
    }
};
