class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        long num = 0;
        vector<bool> ans;
        for (int n : nums) {
            // Use the fact that (ab + c)%d is same as ((a%d)(b%d) + c%d)%d.
            num = (num * 2 + n) % 5;
            if (num % 5 == 0) {
                ans.push_back(true);

            } else {
                ans.push_back(false);
            }
        }
        return ans;
    }
};

