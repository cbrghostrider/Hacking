class Solution {
public:
    
    int totalCandies(const vector<int>& boxes) {
        int total = 0;
        for (const int candies: boxes) {
            total += candies;
        }
        return total;
    }
    
    // n2 candy swap
    vector<int> n2CandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
        int aliceCandies = totalCandies(aliceSizes);
        int bobCandies = totalCandies(bobSizes);
        
        for (const int alice : aliceSizes) {
            for (const int bob : bobSizes) {
                int newAliceCandies = aliceCandies - alice + bob;
                int newBobCandies = bobCandies - bob + alice;
                if (newAliceCandies == newBobCandies) {
                    return {alice, bob};
                }
            }
        }
        return {0, 0};
    }
    
    bool binarySearch(const vector<int>& nums, int left, int right, int num) {
        if (right - left <= 1) {
            if (nums[left] == num || nums[right] == num) {
                return true;
            }
            return false;
        }
        
        int mid = ((long long)left + right)/2;
        if (nums[mid] == num) {
            return true;
        } else if (nums[mid] > num) {
            return binarySearch(nums, left, mid, num);
        }
        return binarySearch(nums, mid, right, num);
    }
    
    // nlogn candy swap
    // for each box of alice's, you find if the box with "needed" number is in bob's list using binary search.
    vector<int> nlognCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
        std::sort(aliceSizes.begin(), aliceSizes.end());
        std::sort(bobSizes.begin(), bobSizes.end());
        
        int aliceCandies = totalCandies(aliceSizes);
        int bobCandies = totalCandies(bobSizes);
        
        for (int ap=0; ap < aliceSizes.size(); ap++) {
            int alice = aliceSizes[ap];
            int newAliceSize = aliceCandies - alice;
            int newBobSize = bobCandies + alice;
            
            int excessBob = newBobSize - newAliceSize;
            int bobMustGive = excessBob/2;
            
            if (bobMustGive < 0) {
                continue;
            }
            if (binarySearch(bobSizes, 0, bobSizes.size() - 1, bobMustGive)) {
                return {alice, bobMustGive};
            }
        }
        return {-1, -1};
    }
    
    vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
        return nlognCandySwap(aliceSizes, bobSizes);
    }
};
