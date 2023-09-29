class Solution {
public:
    // O(n) time.
    vector<int> findBuildings(vector<int>& heights) {
        vector<int> ans;
        int largest=0;
        for (int i=heights.size()-1; i>=0; i--) {
            if (heights[i] > largest) {
                ans.push_back(i);
                largest = heights[i];
            }
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
