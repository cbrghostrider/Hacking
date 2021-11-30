class Solution {
public:
    // O(n) time, O(n) space.
    // Uses monotonic stack.
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ans(temperatures.size(), 0);
        vector<std::pair<int, int>> stack;
        
        for (int i=temperatures.size()-1; i>=0; i--) {
            int curr = temperatures[i];
            while (!stack.empty() && stack.back().first <= curr) {stack.pop_back();}
            if (stack.empty()) {ans[i] = 0;} else {ans[i] = stack.back().second - i;}
            stack.push_back(make_pair(curr, i));
        }
        return ans;
    }
};
