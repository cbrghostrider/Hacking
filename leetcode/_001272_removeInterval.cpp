class Solution {
    
public:
    // O(n) time, O(n) space for ans.
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<vector<int>> ans;
        const int remove_start = toBeRemoved[0];
        const int remove_end = toBeRemoved[1];
        
        for (int i=0; i<intervals.size(); i++) {
            int my_start = intervals[i][0];
            int my_end = intervals[i][1];
            if (remove_start <= my_start && remove_end >= my_end) {
                continue;
            } else if (remove_start > my_start && remove_end < my_end) {
                ans.push_back({my_start, remove_start});
                ans.push_back({remove_end, my_end});
            } else if (remove_end <= my_start || remove_start >= my_end) {
                ans.push_back(intervals[i]);
            } else if (my_start < remove_end && remove_end < my_end) {
                ans.push_back({remove_end, my_end});
            } else if (remove_start <= my_end && my_start < remove_start) {
                ans.push_back({my_start, remove_start});
            }
        }
        
        return ans;
    }
};
