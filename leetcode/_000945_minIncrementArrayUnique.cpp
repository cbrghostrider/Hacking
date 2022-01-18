class Solution {
    
    // sum of first k natural numbers
    int computeSeries(int k) {
        return (k * (k+1) / 2);
    }
    
public:
    // O(n log n) for creating the map.
    // O(n + log n) for iterating through the map in order
    // O(n log n) over all time, O(n) space.
    int minIncrementForUnique(vector<int>& nums) {
        map<int, int> freqs;
        for (int n : nums) { freqs[n]++; }
        
        int count=0;
        for (auto it=freqs.begin(); it != freqs.end(); it++) {
            int val = it->first;
            int freq = it->second;
            
            if (freq == 1) { continue; }
            if (std::next(it) == freqs.end()) {
                count += computeSeries(freq-1);
                break;
            }
            
            auto it2 = std::next(it);
            int next_val = it2->first;
            
            // if everything can be accommodated in the gap between val and next_val
            if (next_val - val >= freq) {
                count += computeSeries(freq-1);
                continue;
            }
            
            // 1 of freq can stay
            // next_val - val - 1 number of them are in series
            // the rest carry over
            int carry_over = freq - 1 - (next_val - val - 1);
            freqs[next_val] += carry_over;
            count += carry_over * (next_val - val);
            
            count += computeSeries(next_val - val - 1);
        }
        
        return count;
    }
};
