class Solution {
    // canShip will return whether the given weights can be shipped in "days" days, using a ship of capacity "capacity".
    // It does this in O(n) time.
    bool canShip(const vector<int>& weights, int days, int capacity) {
        int days_taken=0;
        int sum=0;
        for (int i=0; i<weights.size(); i++) {
            if (sum + weights[i] > capacity) {
                days_taken++;  // ship the last group
                sum = weights[i];
            } else {
                sum += weights[i];
            }
            if (days_taken > days) return false;
        }
        if (sum > 0) days_taken++;  // for the last group that was in progress
        return (days_taken <= days);
    }
    
    int binSearchCapacity(const vector<int>& weights, int days, int wt_lo, int wt_hi) {
        if (wt_lo == wt_hi) return wt_lo;
        if (wt_lo + 1 == wt_hi) {
            if (canShip(weights, days, wt_lo)) return wt_lo;
            return wt_hi;
        }
        int wt_mid = (wt_lo+wt_hi)/2;
        if (canShip(weights, days, wt_mid)) {
            return binSearchCapacity(weights, days, wt_lo, wt_mid);
        }
        return binSearchCapacity(weights, days, wt_mid, wt_hi);
    }
    
public:
    // Uses binary search to guess the weight of the ship. 
    // The guess is bounded below by the max weight of an item.
    // The guess is bounded above by the total weight of all items.
    // Binary search runtime is O(log n) for constant work, but here each confirmation during a search takes O(n).
    // Total runtime: O(nlogn), space O(1).
    int shipWithinDays(vector<int>& weights, int days) {
        int wt_lo=0, wt_hi=0;
        for (int w : weights) {
            if (w > wt_lo) {wt_lo = w;}
            wt_hi += w;
        }
        return binSearchCapacity(weights, days, wt_lo, wt_hi);
    }
};
