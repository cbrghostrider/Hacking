class Solution {
    struct Info {
        int start=0;  // inclusive
        int end=0;    // inclusive
    };
public:
    // O(n log n) time for sort.
    // O(n) time for Info vector.
    int minTaps(int n, vector<int>& taps) {
        vector<Info> ranges;
        for (int i=0; i<=n; i++) {
            ranges.push_back({i-taps[i], i+taps[i]});
        }
        
        std::sort(ranges.begin(), ranges.end(), [](const Info& lhs, const Info& rhs) -> bool {
            if (lhs.start != rhs.start) return lhs.start < rhs.start;
            return lhs.end > rhs.end;
        });
        
        int tap_count=0;
        int coord=0, index=0; 
        if (coord > 0) return -1;
        
        while (index < ranges.size() && coord < n) {
            // Add everything that covers coord and beyond
            int found_end=-200;  // out of bounds
            while (index < ranges.size() && ranges[index].start <= coord) {
                if (ranges[index].end > found_end) {
                    found_end = std::max(ranges[index].end, found_end);                    
                }
                index++;
            }
            
            if (found_end == -200) {
                // point coord not covered!
                return -1;
            }
            
            coord = found_end;            
            tap_count++;            
        }
        
        if (coord < n) return -1;
        return tap_count;
    }
};
