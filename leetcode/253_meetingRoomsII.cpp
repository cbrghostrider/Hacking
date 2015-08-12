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
    vector<bool> canUseSameRoom(vector<Interval>& intervals) {
        vector<bool> usage(intervals.size(), true);
        int lastEnd = std::numeric_limits<int>::min();
        for (int i=0; i<intervals.size(); i++) {
            const Interval& inter = intervals[i];
            if (inter.start < lastEnd) {
                usage[i] = false;
                continue;
            }
            lastEnd = inter.end;
        }
        return usage;
    }
    
    //schedules maximum possible into one room, and returns those that couldn't get into that room
    vector<Interval> scheduleRoom(vector<Interval>& intervals) {
        vector<bool> usage = canUseSameRoom(intervals);
        vector<Interval> retval;
        for (int i=0; i<intervals.size(); i++) {
            if (usage[i] == false) retval.push_back(intervals[i]);
        }
        return retval;
    }
    
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [] (const Interval& lhs, const Interval& rhs) -> bool {
            if (lhs.start != rhs.start) {
                return (lhs.start < rhs.start);
            } else {
                return ((lhs.end-lhs.start) < (rhs.end-rhs.start));
            }
        });
        
        int rooms = 0;
        while (intervals.size()) {
            intervals = scheduleRoom(intervals);
            rooms++;
        }
        return rooms;
    }
};
