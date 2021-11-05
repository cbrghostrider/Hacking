class Solution {
public:
    vector<int> decompressRLElist(vector<int>& nums) {
        vector<int> ans;
        for (int ptr=0; ptr<nums.size(); ptr+=2) {
            int freq = nums[ptr];
            int value = nums[ptr+1];
            for (int i=0; i<freq; i++) ans.push_back(value);
        }
        return ans;
    }
};
