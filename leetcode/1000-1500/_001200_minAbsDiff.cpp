class Solution {
public:
    // O(nlogn) time, O(n) space
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
        vector<vector<int>> ans;
        int min = std::numeric_limits<int>::max();
        for (int i=1; i<arr.size(); i++) {
            int diff = std::abs(arr[i] - arr[i-1]);
            if (diff < min) {
                min = diff;
                ans.clear();
                ans.push_back({arr[i-1], arr[i]});
            } else if (diff == min) {
                ans.push_back({arr[i-1], arr[i]});
            }
        }
        return ans;
    }
};
