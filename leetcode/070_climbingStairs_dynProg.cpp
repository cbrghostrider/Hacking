// O(n) time and O(n) space
// Since we only need previous 2 ways, space can be reduced to O(1)
class Solution {
public:
    int climbStairs(int n) {
        
        //dynamic programming cache
        int ways[n+1];
        ways[0] = 0; ways[1] = 1; ways[2] = 2;
        
        //dynamic programming loop
        for (int s=3; s<=n; s++) {
            ways[s] = ways[s-1] + ways[s-2];
        }
        
        return ways[n];
    }
};
