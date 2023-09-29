class Solution {
    struct Info {
        int index=-1;
        int start=-1;
        int end=-1;
    };
    
    function<bool(const Info&, const Info&)> comp = [this](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.start != rhs.start) return lhs.start > rhs.start;  // earlier start time goes first
        int len1 = lhs.end-lhs.start+1;
        int len2 = rhs.end-rhs.start+1;
        if (len1 != len2) return len1>len2;  // shorter len goes first
        return lhs.index > rhs.index;  // earlier index goes first (tie-breaker)
    };
    using MinHeap = priority_queue<Info, vector<Info>, decltype(comp)>;
    MinHeap min_heap;
    
public:
    // O(n^2 log n) time, O(n) space.
    int maxEvents(vector<vector<int>>& events) {
        min_heap = MinHeap(comp);
        
        for (int i=0; i<events.size(); i++) {
            Info info = {i, events[i][0], events[i][1]};
            min_heap.push(info);
        }
        
        int attended=0;
        int curr_time=0;
        while (!min_heap.empty()) {
            auto elem=min_heap.top(); min_heap.pop();
            
            if (elem.start > elem.end) {  // can't attend this event anymore
                continue;
            }
            
            if (elem.start < curr_time) { // couldn't attend the earlier part of the event
                elem.start = curr_time;
                if (elem.start <= elem.end) { min_heap.push(elem); }
                continue;
            }
            
            //attend this event
            attended++;
            curr_time = elem.start+1;
        }
        return attended;
    }
};
