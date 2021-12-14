class Solution {
public:
    // Usually we could search the entire range [1..n] and count "how many times does x appear"
    // This would be O(n^2)
    // But instead, we can binary search within this range, and count "how many numbers are  <= x"
    // This will be O(nlogn)
    int findDuplicate(vector<int>& nums) {
        // binary search ranges at any time
        int lo=1, hi=nums.size()-1;
        
        while (1) {
            if (lo == hi) return lo;
            int search = (hi+lo)/2;
            int count=0;
            for (int i=0; i<nums.size(); i++) {
                if (nums[i] <= search) {count++;}
            }
            if (count <= search) {
                lo = search+1;
            } else {
                hi = search;
            }
        }
        return -1;  // should not get here
    }
};
