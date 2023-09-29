class NumArray {
    vector<long> cumulative;
public:
    NumArray(vector<int>& nums) {
        long sum = 0;
        for (int n : nums) {
            sum += n;
            cumulative.push_back(sum);
        }
    }
    
    int sumRange(int left, int right) {
        if (left == 0) return cumulative[right];
        return (cumulative[right] - cumulative[left-1]);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
