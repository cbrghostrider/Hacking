class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        vector<int> ns;  // non-zero numbers
        
        bool has_zero = false;
        for (int n : nums) {
            if (n == 0) { has_zero = true; } else {ns.push_back(n);}    
        }
        
        std::sort(ns.begin(), ns.end());
        const int sz = ns.size();
        if (sz < 3) return 0;
        int p1 = ns[sz-1] * ns[sz-2] * ns[sz-3];  // if 3 positives or 3 negatives is maxprod.
        int p2 = ns[0] * ns[1] * ns[sz-1];  // 2 negs and 1 positive is maxprod.
        int max = std::max(p1, p2);
        if (has_zero) return std::max(0, max);  // one zero, rest negs.
        return max;
    }
};
