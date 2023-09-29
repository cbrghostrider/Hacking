class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int last_distance = k;
        for (int n : nums) {
            if (n == 1) {
                if (last_distance < k) return false;
                last_distance = 0;
            } else {
                last_distance++;
            }
        }
        return true;
    }
};
