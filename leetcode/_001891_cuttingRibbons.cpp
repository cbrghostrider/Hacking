class Solution {
    map<int, int> counts;
    
    bool possiblePCut(int p, int k) {
        int count=0;
        for (auto it=counts.rbegin(); it != counts.rend(); it++) {
            int num_pieces = it->first/p;
            count += num_pieces * it->second;
            if (count >= k) return true;
        }
        return false;
    }
    
    int search(int lo, int hi, int k) {
        if (lo == hi) return lo;
        if (lo + 1 == hi) {
            if (possiblePCut(hi, k)) return hi;
            return lo;
        }
        int mid = (lo+hi)/2;
        if (possiblePCut(mid, k)) {
            return search(mid, hi, k);
        }
        return search(lo, mid-1, k);
    }
public:
    // O(n log n) time, O(n) space.
    int maxLength(vector<int>& ribbons, int k) {
        long sum=0;
        for (int n : ribbons) {counts[n]++; sum += n;}
        if (sum < k) return 0;
        
        return search(1, counts.rbegin()->first, k);
    }
};
