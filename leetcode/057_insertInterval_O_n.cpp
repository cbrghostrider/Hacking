class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        if (intervals.size() == 0) return vector<Interval>(1, newInterval);
        vector<Interval> retval;

        bool consumed = false;
        std::for_each(intervals.begin(), intervals.end(), [&retval, &newInterval, &consumed] 
	  (const Interval& inv) -> void {
            if (consumed || newInterval.start > inv.end) {
                retval.push_back(inv);
                return;
            }
            if (newInterval.end < inv.start) {
                retval.push_back(newInterval);
                retval.push_back(inv);
                consumed = true;
                return;
            }
            if (newInterval.start >= inv.start && newInterval.end <= inv.end) {
                retval.push_back(inv);
                consumed = true;
                return;
            }
            if (newInterval.start >= inv.start && newInterval.start <= inv.end) {
                newInterval.start = inv.start;
            }
            if (newInterval.end >= inv.start && newInterval.end <= inv.end) {
                newInterval.end = inv.end;
            }
        });
        if (!consumed) {
            retval.push_back(newInterval);
        }
        return retval;
    }
};
