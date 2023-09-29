class Solution {
public:
    // O(n log n) time, O(1) space.
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), 
                  [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[0] != rhs[0]) return lhs[0] < rhs[0];
            return lhs[1] < rhs[1];
        });
        
        int removals = 0;
        vector<int> last = intervals[0];
        for (int i=1; i<intervals.size(); i++) {
            if (intervals[i][0] >= last[1]) {
                last = intervals[i];
                continue;
            }
            removals++;
            if (intervals[i][1] < last[1]) {
                last = intervals[i];
            }
        }
        return removals;
    }
};
