class Solution {
public:
    vector<int> diStringMatch(string s) {
        int num_i = 0, num_d = 0;
        for_each(s.begin(), s.end(), [&num_i, &num_d](char c) {
            if (c == 'I') num_i++;
            if (c == 'D') num_d++;
        });
        
        int total_nums = s.size() + 1;
        int seed = total_nums - num_i - 1;
        int next_inc = seed+1;
        int next_dec = seed-1;
        vector<int> ans;
        ans.push_back(seed);
        for (char c : s) {
            if (c == 'I') ans.push_back(next_inc++);
            if (c == 'D') ans.push_back(next_dec--);
        }
        return ans;
    }
};
