class Solution {
public:
    
    int getCandidateInternal(const vector<int>& nums, int num_i, int k, int left, int right) {
        // termination condition 
        if (right - left <= 1) {
            if (nums[right] + num_i < k) {
                return nums[right] + num_i;
            }
            if (nums[left] + num_i < k) {
                return nums[left] + num_i;
            }
            return -1;
        }
        
        int mid = ((long long)left + right) / 2;
        if (nums[mid] + num_i == k-1) {
            return nums[mid] + num_i;
        }
        if (nums[mid + 1] + num_i < k) {
            return getCandidateInternal(nums, num_i, k, mid, right);
        }
        return getCandidateInternal(nums, num_i, k, left, mid);
    }
    
    // for "index" (nums[index] = nums_i) and limit "k", 
    // binary search "num_j" giving a "sum" that is closest to but not greater than k.
    // return the "sum" thus found.
    int getCandidateMaxSum(const vector<int>& nums, int index, int k) {
        if (index == 0) {
            return -1;
        }
        return getCandidateInternal(nums, nums[index], k, 0, index-1);
    }
    
    // nlogn solution
    int twoSumLessThanK(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        
        int startIndex = nums.size() - 1;
        for (; startIndex >=0; startIndex--) {
            if (nums[startIndex] < k) {
                break;
            }
        }
        if (startIndex < 0) {
            return -1;
        }
        
        int maxSum = -1;
        for (int index = startIndex; index >=0; index--) {
            int candidate = getCandidateMaxSum(nums, index, k);
            if (candidate > maxSum) {
                maxSum = candidate;
            }
        }
        return maxSum;
    }
};
