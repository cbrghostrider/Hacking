class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> result(digits.size(), 0);
        int carry = 1;
        for (int ctr=digits.size()-1; ctr>=0; ctr--) {
            int res = carry + digits[ctr];
            result[ctr] = res % 10;
            carry = res / 10;
        }
        if (carry) result.insert(result.begin(), 1);
        return result;
    }
};
