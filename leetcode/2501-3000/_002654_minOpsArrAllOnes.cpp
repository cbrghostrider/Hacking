class Solution {
    int gcd(int a, int b) {
        if (a < b) return gcd(b, a);
        if (b == 0) return a;
        return gcd(b, a % b);
    }

public:
    int minOperations(vector<int>& nums) {        
        int count=0;
        for (int n : nums) {
           if (n == 1) {count++;}
        }
        if (count > 0) {
            return nums.size() - count;
        }
        bool found = false;
        int min_ops = std::numeric_limits<int>::max();
        for (int i=0; i<nums.size(); i++) {
            count=0;            
            int gg = nums[i];
            for (int j=i+1; j<nums.size(); j++) {
                count++;
                gg = gcd(gg, nums[j]);
                if (gg == 1) {
                    found = true;
                    if (count < min_ops) {min_ops = count;}
                    break;
                }
            }  
        }
        if (!found) return -1;
        return min_ops + nums.size() - 1;
    }
};
