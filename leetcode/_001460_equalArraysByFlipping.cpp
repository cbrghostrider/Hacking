class Solution {
    // checks if target{left, right} matches reverse(arr{left, right})
    bool revMatch(const vector<int>& target, const vector<int>& arr, int left_ptr, int right_ptr) {
        for (int ptr_r=right_ptr, ptr_l=left_ptr; ptr_r>=left_ptr && ptr_l <= right_ptr; ptr_r--, ptr_l++) {
            if (arr[ptr_r] != target[ptr_l]) return false;
        }
        return true;
    }
    
public:
    // Check if the same numbers occur in the same frequencies. No more no less exactly.
    // If this condition holds, then, we can theoretically apply the following algorithm:
    // Find the first number in the target array, in arr (say index i).
    // Flip everything from [0, i] in arr.
    // Now the first number in both arrays are the same. 
    // Also importantly, starting from the next index, our original condition still holds (nums and freqs match).
    // So recursively apply the same transformation one index at a time.
    // So to answer the question it is enough to check that the same numbers occur at the same frequencies in both.
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> freq_t, freq_a;
        for (int n : target) {freq_t[n]++;}
        for (int n : arr) {freq_a[n]++;}
        if (freq_t.size() != freq_a.size()) return false;
        for (const auto& kv : freq_t) {
            if (freq_a[kv.first] != kv.second) return false;
        }
        return true;
    }
    
};
