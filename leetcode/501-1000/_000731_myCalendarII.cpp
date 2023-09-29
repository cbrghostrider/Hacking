class MyCalendarTwo {
    struct Interval {
        int start=0;  // inclusive
        int end=0;    // non-inclusive
        int count=0;  // 1 or 2 only
    };
    
    // sorted and disjoint
    vector<Interval> intervals;
    
public:
    MyCalendarTwo() {}            
    
    // O(n) time for booking.
    // O(n^2) for all n bookings.
    bool book(int start, int end) {        
        auto& iii = intervals;
        // temp will supersede intervals if all goes well
        vector<Interval> temp;
        
        if (intervals.size() == 0 || start < intervals[0].start) {
            if (intervals.size() == 0 || end <= intervals[0].start) {
                intervals.insert(intervals.begin(), {start, end, 1});
                return true;
            }
            temp.push_back({start, intervals[0].start, 1});
            start = intervals[0].start;
        }
        
        int i=0;
        for (; i<intervals.size(); i++) {
            if (intervals[i].end <= start) {
                // existing interval completely to the left of new one
                temp.push_back(intervals[i]);
                continue;
            }
            
            if (intervals[i].start >= end) {
                // new interval completely to the left of existing one
                if (start != end) temp.push_back({start, end, 1});
                break;
            }
            
            // there is overlap
            if (intervals[i].start <= start && end <= intervals[i].end) {
                // new interval completely encapsulated by existing one
                if (intervals[i].start != start) {
                    temp.push_back({intervals[i].start, start, intervals[i].count});                
                }
                
                int check_count = 1 + intervals[i].count;
                if (check_count > 2) {return false;}
                temp.push_back({start, end, check_count});                
                
                if (end != intervals[i].end) {
                    temp.push_back({end, intervals[i].end, intervals[i].count});
                }                
            } else if (start <= intervals[i].start && intervals[i].end <= end) {
                // existing interval completely encapsulated by new one
                temp.push_back({start, intervals[i].start, 1});
                int check_count = 1 + intervals[i].count;
                if (check_count > 2) {return false;}
                temp.push_back({intervals[i].start, intervals[i].end, check_count});
                start = intervals[i].end;  // continues on with the next index i
            } else if (start < intervals[i].start) {
                // new interval starts to the left of the existing one (and ends in the middle)
                temp.push_back({start, intervals[i].start, 1});
                int check_count = 1 + intervals[i].count;
                if (check_count > 2) {return false;}
                temp.push_back({intervals[i].start, end, check_count});
                temp.push_back({end, intervals[i].end, intervals[i].count});
            } else if (intervals[i].start < start) {
                // existing interval starts to the left of the new one (and ends in the middle)
                temp.push_back({intervals[i].start, start, intervals[i].count});
                int check_count = 1 + intervals[i].count;
                if (check_count > 2) {return false;}
                temp.push_back({start, intervals[i].end, check_count}); 
                start = intervals[i].end;  // continues on with the next index i
            }
            
        }                
        
        if (i < intervals.size()) {
            temp.insert(temp.end(), intervals.begin()+i, intervals.end());
        }
        
        if (intervals.back().end <= start) {            
            if (start != end) temp.push_back({start, end, 1});
        }
        
        intervals = temp;
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
