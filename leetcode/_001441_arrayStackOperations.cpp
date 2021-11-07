class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> ans;
        int index = 0;
        int curr_num = 1;
        while (curr_num <= target.back()) {
            if (target[index] == curr_num++) {
                ans.push_back("Push");
                index++;
            } else {
                ans.push_back("Push");
                ans.push_back("Pop");
            }
        }
        return ans;
    }
};
