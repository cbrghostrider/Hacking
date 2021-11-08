class Solution {
public:
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        vector<int> ptimes(26, 0);  // for all 26 English chars.
        int prev_rel = 0;
        for (int i=0; i<releaseTimes.size(); i++) {
            char curr_char = keysPressed[i];
            int curr_time = releaseTimes[i] - prev_rel;
            prev_rel = releaseTimes[i];
            if (ptimes[curr_char - 'a'] < curr_time) {
                ptimes[curr_char - 'a'] = curr_time;
            }
        }
        char ans = 'a';
        int max_time = ptimes[0];
        for (int i=0; i<26; i++) {
            if (ptimes[i] > max_time) {
                max_time = ptimes[i];
                ans = 'a' + i;
            } else if (ptimes[i] == max_time && 'a'+i > ans) {
                ans = 'a' + i;
            }
        }
        return ans;
    }
};
