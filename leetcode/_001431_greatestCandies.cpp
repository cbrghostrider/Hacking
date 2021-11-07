class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> ans;
        int max = std::numeric_limits<int>::min();
        for (int n : candies) {if (n > max) max = n;}
        for (int n : candies) {
            if (n + extraCandies >= max) {
                ans.push_back(true);
            } else {
                ans.push_back(false);
            }
        }
        return ans;
    }
};
