class Solution {
    
    // Put all start and end points in the same heap, but separately.
    // keep a running list of "opened" intervals while running through the sorted list
    // when you come to a "end" point, you *have* to include at least 2 from that interval
    // choose the end point and the start before it (with caveat), because that will cover all open intervals
    //
    // Caveat: The only catch is when start/end of different intervals overlap
    // at such a time, we don't want to pick the already picked prev start (it was picked in prev end)
    // so keep looking further
    
    struct Info {
        int val=0;
        bool is_end=false;
        int index=0;
    };
    
    function<bool(const Info& lhs, const Info& rhs)> comp = [](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.val != rhs.val) return lhs.val > rhs.val;
        if (lhs.is_end != rhs.is_end) {
            if (lhs.is_end == true) return false;
            return true;
        }
        return lhs.index > rhs.index;
    };
    
    using MinHeap=priority_queue<Info, vector<Info>, decltype(comp)>;
    
public:
    // 
    // Solution basic idea is correct, but it is currently buggy!
    // Needs improvement and simplification along with debugging.
    //
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        MinHeap heap(comp);
        
        // key: interval index,
        // value: how many points in this interval covered so far.
        unordered_map<int, int> covered;
        
        // the actual points chosen        
        unordered_set<int> chosen;
        
        for (int i=0; i<intervals.size(); i++) {
            const auto& ival = intervals[i];
            heap.push({ival[0], false, i});
            heap.push({ival[1], true,  i});
        }
        
        vector<Info> running;
        
        while (!heap.empty()) {
            auto elem = heap.top(); heap.pop();
            if (!elem.is_end) {
                if (chosen.find(elem.val) != chosen.end()) {            
                    // this segment start overlaps with some prev end
                    covered[elem.index] = 1;
                }
                running.push_back(elem);
                continue;
            }
            
            // ignore future end points if this segment was already covered with 2
            if (covered[elem.index] >= 2) {
                continue;
            }
            
            if (chosen.find(elem.val) != chosen.end()) continue;
            
            // pick this end point
            chosen.insert(elem.val);
            covered[elem.index]++;
            
            if (covered[elem.index] >= 2) {
                vector<int> erase_inds;
                for (int i=running.size()-1; i>=0; i--) {
                    covered[running[i].index]++;
                    if (covered[running[i].index] >= 2) {                        
                        erase_inds.push_back(i);
                    }
                    if (running[i].index == elem.index) break;
                }
                for (int i=0; i<erase_inds.size(); i++) {
                    running.erase(begin(running) + erase_inds[i]);
                }
                continue;
            }
            
            // these two points (curr end, and the start before it)
            // will also cover 2x all the started but not ended seen so far
            // a corner case happens when start/end of different segments overlap...
            for (int i=running.size()-1; i>=0; i--) {
                if (covered[running[i].index] >= 1 && running[i].index != elem.index) { 
                    continue; 
                }                                    
                chosen.insert(running[i].val);
                break;
            }
            for (int i=0; i<running.size(); i++) {
                covered[running[i].index] = 2;
            }
            
            running.clear();                       
        }
        
        return chosen.size() + (running.empty() ? 0 : 1);
    }
};
