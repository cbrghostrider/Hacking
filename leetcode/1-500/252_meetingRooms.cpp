// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [] (const Interval& lhs, const Interval& rhs) -> bool {
            if (lhs.start != rhs.start) {
                return (lhs.start < rhs.start);
            } else {
                return ((lhs.end-lhs.start) < (rhs.end-rhs.start));
            }
        });
        int lastEnd = std::numeric_limits<int>::min();
        int scheduled = 0;
        for (const Interval& inter : intervals) {
            if (inter.start < lastEnd) continue;
            scheduled++;
            lastEnd = inter.end;
        }
        return (scheduled == intervals.size());
    }
};
