/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
    struct Info {
        int val=0;              // start OR end time
        bool is_start = false;  // is val for start or end
        int index=0;            // the schedule ID (index) for this start/end
    };
        
public:
    // O(n log n) time, O(n) space.
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        unordered_set<int> in_progress;  // records the schedule ID for employees currently working
        
        vector<Info> infos;
        for (int i=0; i < schedule.size(); i++) {
            for (const Interval& inter : schedule[i]) {
                infos.push_back({inter.start, true,  i});
                infos.push_back({inter.end, false, i});                                
            }
        }
        
        std::sort(infos.begin(), infos.end(), [](const Info& lhs, const Info& rhs) -> bool {
            if (lhs.val != rhs.val) return lhs.val < rhs.val;
            if (lhs.is_start != rhs.is_start) {
                return (lhs.is_start ? false : true);
            }
            return lhs.index < rhs.index;
        });
        
        vector<Interval> ans;
        int last_free=-1;  // 
        for (const Info& info : infos) {
            if (in_progress.size() == 0 && last_free != -1  && info.is_start && last_free != info.val) {
                ans.push_back(Interval(last_free, info.val));                
            }
            if (info.is_start) {
                in_progress.insert(info.index);
            } else {
                in_progress.erase(info.index);
            }
            if (in_progress.size() == 0 && !info.is_start) {
                last_free = info.val;
            }
        }
        return ans;
    }
};
