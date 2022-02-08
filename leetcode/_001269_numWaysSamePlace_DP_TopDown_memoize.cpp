class Solution {
    int LENGTH;
    
    // memoization cache
    unordered_map<int, long> cache;
    
    int signature(int cur, int steps) {
        return ((cur << 10) | (steps));
    }
    
    // cur is where the ptr currently resides, steps is number of steps left to go
    // returns the number of ways ptr ends at index 0
    long numWaysInternal(int cur, int steps) {
        int sig = signature(cur, steps);
        if (cache.find(sig) != cache.end()) {return cache[sig];}
        
        if (steps == 0) {
            cache[sig] = (cur == 0 ? 1 : 0);
            return cache[sig];
        }
        
        long lhs  = cur-1 < 0       ? 0 : numWaysInternal(cur-1, steps-1);
        long stay = numWaysInternal(cur, steps-1);
        long rhs  = cur+1 == LENGTH ? 0 : numWaysInternal(cur+1, steps-1);
        
        long ret = lhs + stay + rhs;
        ret %= 1000000007;
        
        cache[sig] = ret;
        return ret;
    }
    
public:
    // O(arrLen + steps) time, O(arrLen + steps) space.
    // Even though the upper bound on cache key is (arrLen * steps), 
    // only (arrLen + steps) would be explored.
    int numWays(int steps, int arrLen) {
        LENGTH = arrLen;
        return numWaysInternal(0, steps);
    }
};
