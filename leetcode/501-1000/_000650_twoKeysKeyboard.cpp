class Solution {
vector<int> cache;

// Solves for n==val;
int steps(int val) {
    if (cache[val] != -1) return cache[val];
    int ret = val;  // worst case, 1 copy + (val-1) pastes.

    // We try to bring the number to dd, and then copy it x number of times to get to val.
    for (int dd=2; dd <= val/2; dd++) {
        if (val % dd != 0) continue;
        int copy_paste = val/dd + steps(dd);
        ret = std::min(ret, copy_paste);
    }

    cache[val] = ret;
    return ret;
}

public:
    int minSteps(int n) {
        if (n <= 1) return 0;        
        cache = vector<int>(n+1, -1);
        cache[0] = cache[1] = 0;
        cache[2] = 2;        
        return steps(n);
        return -1;
    }
};
