class Solution {
    struct DistInfo {
        int worker=0;
        int bike=0;
        int dist=0;
    };
public:
    // O(mn) time, O(mn) space.
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        auto comp = [](const DistInfo& lhs, const DistInfo& rhs) -> bool {
            if (lhs.dist != rhs.dist) return lhs.dist > rhs.dist;
            if (lhs.worker != rhs.worker) return lhs.worker > rhs.worker;
            return lhs.bike > rhs.bike;
        };
        
        std::priority_queue<DistInfo, vector<DistInfo>, decltype(comp)> min_heap(comp);
        for (int w=0; w<workers.size(); w++) {
            for (int b=0; b<bikes.size(); b++) {
                int w_x=workers[w][0], w_y=workers[w][1];
                int b_x=bikes[b][0], b_y=bikes[b][1];
                int dist = std::abs(w_x-b_x) + std::abs(w_y-b_y);
                min_heap.push({w, b, dist});
            }
        }
        
        vector<int> ans(workers.size(), -1);
        vector<bool> done(bikes.size(), false);
        int unassigned = workers.size();
        while (unassigned > 0) {
            DistInfo info = min_heap.top(); 
            min_heap.pop();
            if (ans[info.worker] != -1) continue;
            if (done[info.bike] == true)  continue;
            
            // Found the most optimal assignment of worker to bike.
            unassigned--;
            ans[info.worker] = info.bike;
            done[info.bike] = true;
        }
        return ans;
    }
};
