class Solution {
    // let nw(x, y) denote the number of ways you can number x as sum of cons pos integers, ending with y
    // i.e. nw(x, y) = ... + .. + .. + y
    // start with y = ceil(x/2), go downwards to 1
    // add all the ways
    // use memoization to speed it up (top down DP)

    unordered_map<string, int> cache;
    
    string signature(int total, int end_num) {
        return ("T-" + std::to_string(total) + "-E-" + std::to_string(end_num));
    }
    
    int num_ways(int total, int end_num) {
        string sig = signature(total, end_num);
        if (cache.find(sig) != cache.end()) return cache[sig];
        if (total <= 0) {
            cache[sig] = 0;
            return 0;
        }
        if (total == end_num) {
            cache[sig] = 1;
            return 1;
        }
        if (end_num == 1 && total > 1) {
            cache[sig] = 0;
            return 0;
        }
        int ans = num_ways(total-end_num, end_num-1);
        cache[sig] = ans;
        return ans;
    }
    
public:    
    // O(n) time algorithm.
    // TLE for problem size of 10^9
    int consecutiveNumbersSum(int n) {
        int mid = n/2;
        if (n%2 != 0) mid++;
        int ans=0;
        for (int i=mid; i>=1; i--) {
            ans += num_ways(n, i);
        }
        return ans + 1;  // for some reason the number by itself is counted as one way
    }
};
