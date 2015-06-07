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
// Running time analysis
// Divide and conquer: T(n) = a*T(n/b) + f(n)
// a = 2, b = 2, f(n) = O(n)
// By the master method, running time of mergePrime = O(n log n)
// Also the initial sort is O(n log n)
class Solution {
    vector<Interval> mergeTwo(vector<Interval>& intervals) {
        if (intervals[0].end < intervals[1].start) return intervals;
        Interval interval;
        interval.start = intervals[0].start;
        interval.end = (intervals[0].end > intervals[1].end) ? intervals[0].end : intervals[1].end;
        return (vector<Interval>(1, interval));
    }
    
    vector<Interval> mergePrime(vector<Interval>& intervals) {
        //base cases
        if (intervals.size() <= 1) return intervals;
        if (intervals.size() == 2) return mergeTwo(intervals);
        
        //inductive case
        int mid = intervals.size()/2;
        vector<Interval> lhs = vector<Interval>(intervals.begin(), intervals.begin()+mid);
        vector<Interval> rhs = vector<Interval>(intervals.begin() + mid, intervals.end());
        intervals.clear();
        
        //recurse
        lhs = mergePrime(lhs);
        rhs = mergePrime(rhs);
        
         //combine
        while (lhs.size() && rhs.size() && lhs[lhs.size()-1].end >= rhs[0].start) {
            Interval lastLhs  = lhs[lhs.size()-1]; 
            lhs.pop_back();
            Interval firstRhs = rhs[0];
            rhs.erase(rhs.begin());
            vector<Interval> mm = {lastLhs, firstRhs};
            mm = mergeTwo(mm);
            lhs.insert(lhs.end(), mm.begin(), mm.end());
        }
        
        //return result
        lhs.insert(lhs.end(), rhs.begin(), rhs.end());
        return lhs;
    }
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](const Interval& lhs, const Interval& rhs) -> bool {
            return ((lhs.start != rhs.start) ? (lhs.start < rhs.start) : (lhs.end < rhs.end));
        });
        return mergePrime(intervals);
    }
};
