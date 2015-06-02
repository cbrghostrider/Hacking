class Solution {
    void closestCheck(int& closestSum, int cand, int target) {
        if (abs(closestSum - target) > abs(cand - target)) closestSum = cand;
    }
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() < 3) return 0; //undefined problem
        std::sort(nums.begin(), nums.end());
        
        int closestSum = nums[0] + nums[1] + nums[2];
        for (int i=0, k=nums.size()-1; i<nums.size()-2; i++) {
            for (int j=i+1; j<nums.size()-1 && j < k; j++) {
                int sumtwo = nums[i] + nums[j];
                int lastNeeded = target - sumtwo;
                //as index j increases, k can only decrease from previous
		//this is because the numbers are sorted, so as j increases, value of sumtwo monotonically increases
		//and therefore value of nums[k] can only monotonically decrease (to be near same target)
                //this is why we can get away with initializing k in the OUTER for loop!
		//over one iteration of the outer (i based) for loop, both j and k are inc and dec no more than n times
		//This is why algorithmic complexity is O(n^2)
                while (k > j+1 && nums[k] > lastNeeded) { 
                    k--;
                }
                if (k != nums.size()-1) {
                    int cand1 = sumtwo + nums[k+1];
                    closestCheck(closestSum, cand1, target);
                }
                int cand2 = sumtwo + nums[k];
                closestCheck(closestSum, cand2, target);
            }
        }
        return closestSum;
    }
};
