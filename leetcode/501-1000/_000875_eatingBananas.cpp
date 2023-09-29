class Solution {

    // If eating at k per hour, how many hours to consume all
     int hours(const vector<int>& piles, int k) {
         int total=0;
         for (int pile : piles) {
             total += pile/k;
             total += (pile % k == 0) ? 0 : 1;
         }
         return total;
    }
    
    // searches for optimal value of k such that h hours can be accomplished.
    int search(const vector<int>& piles, int h, int lo, int hi) {
        if (lo == hi) return lo;
        int mid = (lo+hi)/2;
        int hrs = hours(piles, mid);
        if (hrs <= h) {
            return search(piles, h, lo, mid);
        }
        return search(piles, h, mid+1, hi);
    }
    
public:
    // O(n log m) total time: n = length of piles, m = max size of a pile
    int minEatingSpeed(vector<int>& piles, int h) {
        if (piles.size() > h) return -1;
        int max=0;
        for (int p : piles) {if (p > max) {max = p;}}
        return search(piles, h, 1, max);
    }
};
