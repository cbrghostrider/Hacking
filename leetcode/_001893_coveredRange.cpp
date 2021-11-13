class Solution {
public:
    // O(nlogn) time, O(n) space.
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        std::sort(ranges.begin(), ranges.end(), [](const vector<int>& left, const vector<int>& right)->bool {
           if (left[0] != right[0]) {
               return (left[0] < right[0]);
           } 
           return (left[1] < right[1]);
        }); 
        
        std::priority_queue<int, vector<int>, std::greater<int>> min_heap;
        int last_closed = std::numeric_limits<int>::min();
        int running_count = 0;
        
        for (const vector<int>& range : ranges) {
            int curr_open = range[0];
            int curr_close = range[1];
            
            while (!min_heap.empty() && min_heap.top() < curr_open) {
                last_closed = min_heap.top();
                min_heap.pop();
                running_count--;
            }
            
            if (running_count == 0 && left > last_closed && left < curr_open) { return false; }
            if (running_count == 0 && right > last_closed && right < curr_open) { return false; }
            if (running_count == 0 && left <= last_closed && right >= curr_open
                && (curr_open - last_closed > 1)) {return false;}
            
            running_count++;  // for current open
            min_heap.push(curr_close);
        }
        
        while (!min_heap.empty()) {
            last_closed = min_heap.top();
            min_heap.pop();
            running_count--;
        }
        if (left > last_closed || right > last_closed) return false;
        return true;
    }
};
