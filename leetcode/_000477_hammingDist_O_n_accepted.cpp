class Solution {
    int N;
    
    // counts how many of the N numbers at the given bit position have a 1.
    vector<int> one_counts;
    
    // An xor will only produce a 1 when a one_counts number combines with a non-one-counts number.
    // And we have counts of such for each position!
public:
    // O(n) algorithm.
    int totalHammingDistance(vector<int>& nums) {
        N = nums.size();
        one_counts = vector<int>(32, 0);
        
        uint32_t mask = 0x1;
        int pos=0;
        while (mask) {
            for (int i=0; i < nums.size(); i++) {
                if (mask & nums[i]) {
                    one_counts[pos]++;
                }
            }
            pos++;
            mask <<= 1;
        }
        
        int pop=0;
        for (int n : one_counts) {
            int n_prime = N-n;
            pop += n * n_prime;
        }
        return pop;
    }
};
