class Solution {
public:
    // O(n) space, O(n) time.
    int findSpecialInteger2(vector<int>& arr) {
        const int threshold = arr.size()/4;  // 25% threshold
        unordered_map<int, int> counts;
        for (int n : arr) {counts[n]++;}
        for (const auto& kv : counts) {
            if (kv.second > threshold) return kv.first;
        }
        return -1;
    }
    
    // O(n) time, O(1) space
    int findSpecialInteger(vector<int>& arr) {
        const int threshold = arr.size()/4;  // 25% threshold
        int p1 = 0;
        while (p1 < arr.size()) {
            int p2=p1;
            for (; p2<arr.size(); p2++) {
                if (arr[p1] != arr[p2]) break;
            }
            int count = p2 - p1;
            if (count > threshold) { return arr[p1];}
            p1 = p2;
        }
        return -1;
    }
    
     // Could binary search to do it in O(logn) time.
};
