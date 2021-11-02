class Solution {
public:
    // O(n) time and O(n) space.
    vector<int> findErrorNums2(vector<int>& nums) {
        std::unordered_set<int> ns;
        vector<int> ans;
        for (int n : nums) {
            if (ns.find(n) != ns.end()) {
                ans.push_back(n);
            }
            ns.insert(n);
        }
        for (int i=1; i<=nums.size(); i++)  {
            if (ns.find(i) == ns.end()) {
                ans.push_back(i);
            }
        }
        return ans;
    }
    
    // O(nlogn) time and O(1) space.
    vector<int> findErrorNums3(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int duplicated = 0;
        int sum = nums[0];
        for (int i=1; i<nums.size(); i++) {
            if (duplicated == 0 && nums[i] == nums[i-1]) {
                duplicated = nums[i];
            }
            sum += nums[i];
        }
        int expected_sum = nums.size() * (nums.size() + 1) / 2;
        int missing = expected_sum - (sum - duplicated);
        return {duplicated, missing};
    }
    
    // O(n) time and O(1) space.
    // When each number is encountered, another number at that "index" is checked and multiplied by -1.
    // If already negative, then that "index" is the duplicated number.
    vector<int> findErrorNums(vector<int>& nums) {
        int duplicated = 0;
        for (int i=0; i<nums.size(); i++) {
            int index = std::abs(nums[i]) - 1;
            if (nums[index] < 0) { duplicated = index + 1;}
            nums[index] *= -1;
        }
        int sum = 0;
        for (int i=0; i<nums.size(); i++) {
            nums[i] = std::abs(nums[i]);
            sum += nums[i];
        }
        int expected_sum = nums.size() * (nums.size() + 1) / 2;
        int missing = expected_sum - (sum - duplicated);
        return {duplicated, missing};
    }
};
