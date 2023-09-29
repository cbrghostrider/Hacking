// Attempt 1: Functionally correct solution.
// But TLE on last few cases.
// 707/717 pass, rest TLE.
class Solution {
    // Key: elem; Value: count
    unordered_map<int, int> counts;

    // Only contains the keys.
    priority_queue<int, vector<int>, std::greater<int>> min_heap;

    void add_elem(int elem) {
        if (counts.find(elem) == counts.end()) {
            counts[elem] = 1;
            min_heap.push(elem);
        } else {
            counts[elem]++;
        }
    }
    void remove_elem(int elem) {
        counts[elem]--;
        // Priority queue adjusted in beauty().
    }
    int beauty(int x) {
        vector<int> pops;
        int beauty=0;
        while (!min_heap.empty()) {
            int elem = min_heap.top();
            if (counts[elem] == 0) {
                min_heap.pop();
                counts.erase(elem);
                continue;
            }
            if (x > counts[elem]) {
                x -= counts[elem];
                min_heap.pop();
                pops.push_back(elem);
                continue;
            }            
            beauty = elem;
            for (int p : pops) {
                min_heap.push(p);
            }
            break;            
        }
        return beauty > 0 ? 0 : beauty;
    }
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        // Initialization.
        for (int i=0; i<k; i++) {
            add_elem(nums[i]);
        }
        
        vector<int> result;        
        int b = beauty(x);
        result.push_back(b);
        for (int i=k; i<nums.size(); i++) {
            remove_elem(nums[i-k]);
            add_elem(nums[i]);
            int b = beauty(x);
            result.push_back(b);
        }
        return result;
    }
};
