class Solution {
    struct Data {
        int first_index = -1;
        int last_index = -1;
        int num_times = 0;
    };
    std::unordered_map<int, Data> entries;
    
public:
    // O(n) time, O(n) space
    int findShortestSubArray(vector<int>& nums) {
        int max_count = 0;
        for (int i=0; i<nums.size(); i++) {
            const int num = nums[i];
            if (entries.find(num) == entries.end()) {
                Data data = {i, i, 1};
                entries[num] = data;
            } else {
                entries[num].last_index = i;
                entries[num].num_times++;
            }
            if (entries[num].num_times > max_count) {
                max_count = entries[num].num_times;
            }
        }
        
        int min_length = std::numeric_limits<int>::max();
        for (const std::pair<int, Data>& kv : entries) {
            if (kv.second.num_times < max_count) continue;
            int length = kv.second.last_index - kv.second.first_index + 1;
            if (min_length > length) {
                min_length = length;
            }
        }
        return min_length;
    }
};
