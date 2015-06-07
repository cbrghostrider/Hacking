// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int robPrime(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        
        //dynamic programming cache; money made by robbing *optimal choices* of houses until index i
        vector<int> money(nums.size(), 0);
        money[0] = nums[0];
        money[1] = nums[0] > nums[1] ? nums[0] : nums[1];
        
        //dynamic programming loop
        for (int i=2; i<nums.size(); i++) {
            money[i] = max(nums[i] + money[i-2], money[i-1]);
        }
        return money[nums.size()-1];
    }

    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return (max(nums[0], nums[1]));
        
        int maxmoney=std::numeric_limits<int>::min();
        
        for (int i=0; i<nums.size(); i++) {
            //rob ith house, and delete i, (i-1) and (i+1) th houses
            //then use rob array method from House Robber
            vector<int> houses = nums;
            if (i < (nums.size() - 2)) std::rotate(houses.begin(), houses.begin() + (i+2), houses.end());
            int money = nums[i];
            if (i == nums.size()-1) {
                houses.pop_back();
                houses.pop_back();
                houses.erase(houses.begin());
            } else {
                houses.pop_back();
                houses.pop_back();
                houses.pop_back();
            }

            money += robPrime(houses);
            if (money > maxmoney) {
                maxmoney = money;
            }
        }
        return maxmoney;
    }
};
