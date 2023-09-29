class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        if (s1 == s2) return true;
        if (s1.size() != s2.size()) return false;
        int num_unequals = 0;
        int ind0=-1, ind1=-1;
        for (int i=0; i<s1.size(); i++) {
            if (s1[i] == s2[i]) continue;
            num_unequals++;
            if (num_unequals > 2) return false;
            if (ind0 == -1) {ind0 = i;}
            else if (ind1 == -1) {ind1 = i;}
        }
        if (num_unequals == 1) return false;
        return (s1[ind0] == s2[ind1] && s1[ind1] == s2[ind0]);
    }
};
