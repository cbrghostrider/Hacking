class SparseVector {
    unordered_map<int, int> repr;
    int size = 0;
public:
    
    SparseVector(vector<int> &nums) {
        size = nums.size();
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] == 0) { continue; }
            repr[i] = nums[i];    
        }
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        if (size != vec.size) {return 0;}  // incompatible
        int dp=0;
        for (const auto& kv : vec.repr) {
            if (repr.find(kv.first) == repr.end()) continue;
            dp += kv.second * repr[kv.first];
        }
        return dp;
    }
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
