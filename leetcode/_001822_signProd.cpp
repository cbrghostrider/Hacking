class Solution {
public:
    int arraySign(vector<int>& nums) {
        int num_negs = 0;
        bool has_zero = false;
        for (int n : nums) {
            if (n == 0) {has_zero = true; break;}
            if (n < 0) {num_negs++;}
        }
        if (has_zero) return 0;
        return (num_negs % 2 == 0 ? 1 : -1);
    }
};
