class Solution {
public:
    // O(n log n) time for sort, O(1) space.
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
                                                                
        std::sort(intervals.begin(), intervals.end(), [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[0] != rhs[0]) return lhs[0] < rhs[0];
            return lhs[1] > rhs[1];
        });
        
        int num=0;
        vector<int> last = intervals[0];
        for (int i=1; i<intervals.size(); i++) {
            vector<int>& next = intervals[i];
            if (next[0] >= last[1]) {
                last = next;
                num++;
            } else if (next[1] <= last[1]) {
                // drop it
                ;
            } else {  // next[0] < last[1]  && next[1] > last[1]
                last = next;
                num++;
            }
        }
        num++;
        return num;
    }
};
