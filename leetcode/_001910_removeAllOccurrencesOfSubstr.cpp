class Solution {
public:
    // Brute force.
    // O(n^2 * k) time; k=num removals. O(1) space.
    string removeOccurrences(string s, string part) {
        bool change=true;
        while (change) {
            change = false;            
            for (int i=0; i<s.size(); i++) {
                if (i+part.size() > s.size()) break;
                if (s.substr(i, part.size()) == part) {
                    change = true;
                    s = s.substr(0, i) + s.substr(i+part.size());
                    break;
                }
            }
        }
        return s;
    }
};
