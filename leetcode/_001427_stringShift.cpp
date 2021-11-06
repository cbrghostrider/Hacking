class Solution {
public:
    // O(n) time, O(s) space.
    string stringShift(string s, vector<vector<int>>& shift) {
        if (s.size() == 0 || shift.size() == 0) return s;
        
        int total_left = 0, total_right = 0;
        for (const vector<int>& da : shift) {
            if (da[0] == 0) {
                total_left += da[1];
            } else {
                total_right += da[1];
            }
        }
        
        int len = s.size();
        bool shift_left = (total_left > total_right);
        int total = std::abs(total_left - total_right);
        total %= len;
        
        if (shift_left) {
            string break1 = s.substr(0, total);
            string break2 = s.substr(total);
            return break2 + break1;
        }
        string seg_right = s.substr(s.size() - total);
        string seg_left = s.substr(0, s.size()-total);
        return seg_right + seg_left;
    }
};
