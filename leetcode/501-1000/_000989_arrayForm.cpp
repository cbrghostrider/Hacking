class Solution {
public:
    vector<int> arrayForm(int i) {
        vector<int> ans;
        while (i/10) {
            ans.push_back(i%10);
            i = i/10;
        }
        if (i) {ans.push_back(i);}
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
    
    vector<int> addToArrayForm(vector<int>& nums, int k) {
        int carry = k;
        for (int i=nums.size()-1; i>=0; i--) {
            int num = nums[i] + carry;
            nums[i] = num % 10;
            carry = num/10;
        }
        vector<int> ans = arrayForm(carry);
        ans.insert(ans.end(), nums.begin(), nums.end());
        return ans;
    }
};
