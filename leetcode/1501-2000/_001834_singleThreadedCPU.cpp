class Solution {
    // Task Info
    struct TInfo {
        int ready  = 0;
        int length = 0;
        int index  = 0;
    };
    
    std::function<bool(const TInfo&, const TInfo&)> schedComp = [] (const TInfo& lhs, const TInfo& rhs) -> bool {
        if (lhs.length != rhs.length) {return lhs.length > rhs.length;}
        return lhs.index > rhs.index;
    };
    std::function<bool(const TInfo&, const TInfo&)> readyComp = [] (const TInfo& lhs, const TInfo& rhs) -> bool {
        if (lhs.ready != rhs.ready) {return lhs.ready > rhs.ready;}
        return lhs.index > rhs.index;
    };
    
    using MinHeap1=priority_queue<TInfo, vector<TInfo>, decltype(schedComp)>;
    using MinHeap2=priority_queue<TInfo, vector<TInfo>, decltype(readyComp)>;
    
public:
    // O(n log n) time, O(n) space.
    vector<int> getOrder(vector<vector<int>>& tasks) {
        MinHeap1 sched(schedComp);
        MinHeap2 ready(readyComp);
        
        for (int i=0; i<tasks.size(); i++) {
            const auto& task = tasks[i];
            ready.push({task[0], task[1], i});
        }
        
        vector<int> ans;
        long cur_time=0;
        while (!ready.empty() || !sched.empty()) {
            if (sched.empty() && cur_time < ready.top().ready) {
                cur_time = ready.top().ready;
            }
            
            // Everything that has become ready will be put in the sched heap.
            while (!ready.empty() && ready.top().ready <= cur_time) {
                sched.push(ready.top());
                ready.pop();
            }
            
            auto task = sched.top(); sched.pop();
            ans.push_back(task.index);
            cur_time += task.length;
        }
        
        return ans;
    }
};
