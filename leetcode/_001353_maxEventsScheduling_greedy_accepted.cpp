// Initially set curr_time to the start of the first event.
//
// At any point in the algorithm, we look at all the candidate events that start
// at curr_time or earlier (obviously excluding already scheduled or determined
// unschedulable events)
//
// So initially put all the events that start at curr_time into a min_heap.
// The min_heap maintains heap property based on END TIMES.
// The idea is that out of all the candidates, we schedule one that finishes earliest
// because that way we still have a chance to schedule others after.
// 
// Pick top of heap, schedule it.
// Advance curr time by 1, and add new elements to the heap if they became qualified.
//
// We might also have to throw events out of the heap if their end time at any point
// becomes less than curr_time when we look at them (these are unschedulable events).
//
// If at any point, we have an empty heap, but non-empty consumed events, we fast
// forward curr_time to the start of next event and repeat the process.
class Solution {
    struct Info {
        int index=-1;
        int start=-1;
        int end=-1;
    };
    
    function<bool(const Info&, const Info&)> comp = [this](const Info& lhs, const Info& rhs) -> bool {
        return lhs.end > rhs.end;
    };
    using MinHeap = priority_queue<Info, vector<Info>, decltype(comp)>;
    MinHeap min_heap;
    
public:
    
    // O(n log n) time, O(1) space.
    int maxEvents(vector<vector<int>>& events) {
        std::sort(events.begin(), events.end(), [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[0] != rhs[0]) return lhs[0] < rhs[0];
            int len_l = lhs[1]-lhs[0]+1;
            int len_r = rhs[1]-rhs[0]+1;
            return len_l < len_r;
        });
        
        int attended=0;
        
        MinHeap min_heap(comp);
        int curr_time = events[0][0];
        int s_ptr=0;
            
        while (s_ptr < events.size() || !min_heap.empty()) {
            while (s_ptr < events.size() && events[s_ptr][0] <= curr_time) {
                min_heap.push({s_ptr, events[s_ptr][0], events[s_ptr][1]});
                s_ptr++;
            }
            while (!min_heap.empty() && min_heap.top().end < curr_time) {
                // throw away things that can't be scheduled anymore
                min_heap.pop();
            }
            if (min_heap.empty()) {
                if (s_ptr >= events.size()) break;  // done
                else curr_time = events[s_ptr][0];  // fast-forward
            } else {  // schedule it!
                auto elem = min_heap.top(); min_heap.pop();
                attended++;
                curr_time = std::max(elem.start, curr_time) +1;
            }
        }
                
        return attended;
    }
};
