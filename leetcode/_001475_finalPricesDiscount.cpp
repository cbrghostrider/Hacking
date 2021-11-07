class Solution {
public:
    // O(n) time, O(n) space.
    vector<int> finalPrices(vector<int>& prices) {
        vector<int> mono_stack;
        vector<int> ans;
        for (int i=prices.size()-1; i>=0; i--) {
            while (!mono_stack.empty() && mono_stack.back() > prices[i]) {
                mono_stack.pop_back();
            }
            int cost = (mono_stack.empty() ? prices[i] : prices[i] - mono_stack.back());
            ans.push_back(cost);
            mono_stack.push_back(prices[i]);
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
