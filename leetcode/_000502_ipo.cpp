class Solution {
    // The following WOULD HAVE BEEN the solution if capital was consumed per step
    //
    // At any given point, given current capital w', there will be a set Sx of projects that can be started.
    // We greedily pick project x <- Sx, such that px-cx is largest (px = profit[x], cx = capital[x])
    // Then add px-cx to w', and repeat.
    //
    // But it seems they don't CONSUME the capital to start a new project, it just keeps accumulating...??!?!?
    // so instead of px-cx, we only consider px.
public:
    // O(k*n + n log n) time, O(n) space.
    // This solution is TLE.
    int findMaximizedCapital_(int k, int w, vector<int>& profits, vector<int>& capital) {        
        vector<int> indices;
        for (int i=0; i<profits.size(); i++) {indices.push_back(i);}
        
        std::sort(indices.begin(), indices.end(), [&capital](int lhs, int rhs) -> bool {
            if (capital[lhs] != capital[rhs]) {return capital[lhs] < capital[rhs];}
            return lhs < rhs;
        });
        
        unordered_set<int> picked;        
        long cap = w;
        while (picked.size() < k) {
            int max_gain=std::numeric_limits<int>::min();
            int pick=-1;
            for (int i=0; i<indices.size() && capital[indices[i]] <= cap; i++) {
                int index = indices[i];
                if (picked.find(index) != picked.end()) {continue;}
                int diff = profits[index];
                if (diff > max_gain) {
                    max_gain = diff;
                    pick = index;
                }
            }
            
            if (pick == -1) {
                break;  // can't pick anything anymore
            }            
            cap += max_gain;
            picked.insert(pick);
        }
        
        return cap;
    }
    
    // O(k log n + n log n) time, O(n) space.
    // This solution is accepted.
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {        
        vector<int> indices;
        for (int i=0; i<profits.size(); i++) {indices.push_back(i);}
        
        std::sort(indices.begin(), indices.end(), [&capital](int lhs, int rhs) -> bool {
            if (capital[lhs] != capital[rhs]) {return capital[lhs] < capital[rhs];}
            return lhs < rhs;
        });
        
        priority_queue<int, vector<int>, less<int>> max_heap;
        int picked=0;
        long cap = w;
        int cap_ptr=0;
        
        while (picked < k) {
            while (cap_ptr < indices.size() && capital[indices[cap_ptr]] <= cap) {
                max_heap.push(profits[indices[cap_ptr]]);
                cap_ptr++;
            }
            if (max_heap.empty()) {
                break;  // can't pick anything anymore
            }
            cap += max_heap.top(); max_heap.pop();
            picked++;
        }
                        
        return cap;
    }
    
};
