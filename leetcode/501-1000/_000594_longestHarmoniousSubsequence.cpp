class Solution {

public:
    // O(n) time, O(n) space
    int findLHS(vector<int>& nums) {
        // lengths of subsequences with key as smaller number
        std::unordered_map<int, int> lengths;
    
        // how many of the given (key) numbers have been encountered so far while scanning
        std::unordered_map<int, int> encountered;
    
        // whether the length of subsequence with key is valid
        std::unordered_set<int> valid; 
        
        for (int n : nums) {lengths[n]=0; encountered[n]=0;}
        
        for (int n : nums) {
            encountered[n]++;
            
            if (lengths[n] != 0) {
                lengths[n]++;    
            } else {
                lengths[n] = 1 + encountered[n+1];
                if (encountered[n+1] != 0) {valid.insert(n);}
            }
            if (lengths[n-1] != 0) {
                lengths[n-1]++; 
                valid.insert(n-1);
                valid.insert(n);
            } 
        }
        
        int max = 0;
        for (const std::pair<int, int>& kv : lengths) {
            if (valid.find(kv.first) != valid.end() && kv.second > max) {
                max = kv.second;
            }
        }
        return max;
    }
};
