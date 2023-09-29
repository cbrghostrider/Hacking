class Solution {
public:    
    // If you drop first egg at k-th floor, and:
    //     it breaks: then you have to iteratively test 1->k-1 floors;
    //     if it doesn't break: then you solve the problem recursively for (n-k) floors.
    // At each value of n, we know WITH CERTAINTY whether we can solve the problem, if 
    // one or the other path works. (i.e. egg breaks on k, or we solve it recursively).
    // To solve WITH CERTAINTY means to take the max (worst case) of these choices.
    // num_drops(n) = max(1 + k-1, 1 + num_drops(n-k))
    // 
    // Of course, we don't really know the value of k, so we will try all possible cases
    // with memoization, this becomes DP.
    // 
    // O(n^2) solution.
    int twoEggDrop(int n) {
        if (n <= 2) return n;
        vector<int> drops(n+1, 0);
        drops[1] = 1;
        drops[2] = 2;
        for (int ni=3; ni<=n; ni++) {
            int min = std::numeric_limits<int>::max();
            for (int k=1; k<=ni; k++) {
                int val = std::max(1+k-1, 1+drops[ni-k]);
                if (val < min) {min = val;}
            }
            drops[ni] = min;
        }
        return drops[n];
    }
};
