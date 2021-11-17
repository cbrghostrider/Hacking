class Solution {
public:
    // O(n) time.
    string licenseKeyFormatting(string s, int k) {
        int first_letter_pos = s.find_first_not_of("-");
        if (first_letter_pos == string::npos) return "";
        
        int s_ptr = s.size()-1;
        string ans;
        while (s_ptr >= 0) {
            for (int i=0; i<k && s_ptr >=0; ) {
                char ch = s[s_ptr--];
                if (ch == '-') {
                    continue;
                } else {
                    ans.push_back(std::toupper(ch));
                    i++;
                }
            }
            
            if (s_ptr >=first_letter_pos) ans.push_back('-');
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
