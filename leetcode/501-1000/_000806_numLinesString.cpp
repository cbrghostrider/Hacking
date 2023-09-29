class Solution {
    const int WIDTH = 100;
public:
    vector<int> numberOfLines(vector<int>& widths, string s) {
        int curr_line = 1;
        int curr_width = 0;
        for (char c : s) {
            int len = widths[c - 'a'];
            if (curr_width + len > WIDTH) {
                curr_line++;
                curr_width = len;
            } else {
                curr_width += len;
            }
        }
        return {curr_line, curr_width};
    }
};
