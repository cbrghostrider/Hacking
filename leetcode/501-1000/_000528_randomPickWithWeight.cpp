class Solution {
    vector<int> weights;
    vector<int> csum;
    int total=0;
public:
    // O(n) time for initialization.
    Solution(vector<int>& w) : weights(w) {
        int sum=0;
        for (int wt : weights) {
            sum += wt;
            csum.push_back(sum);
        }
        total = sum;
    }
    
    // O(n) time. 
    // Could make it O(log n) using binary search, since csum is always sorted.
    int pickIndex() {
        int rval = std::rand() % total;
        int prev=0;
        for (int i=0; i<csum.size(); i++) {
            if (rval >= prev && rval < csum[i]) {
                return i;
            }
            prev = csum[i];
        }
        return -1;  // should not happen
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
