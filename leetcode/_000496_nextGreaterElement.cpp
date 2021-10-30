class Solution {
public:
    //////////////////////////////////////////////////////////////////////////
    // Solution 1: HT + brute force search for first greater.
    // O(n * m) time
    // O(m) space
    using Index = int;
    std::unordered_map<int, Index> earliest;

    vector<int> nextGreaterElement2(vector<int>& nums1, vector<int>& nums2) {
        for (int i = nums2.size()-1; i>=0; i--) {
            earliest[nums2[i]] = i;
        }
        
        vector<int> ans;
        for (int i = 0; i<nums1.size(); i++) {
            if (earliest.find(nums1[i]) == earliest.end()){
                ans.push_back(-1);
                continue;
            }
            int number = -1;
            for (int j=earliest[nums1[i]]; j<nums2.size(); j++) {
                if (nums2[j] > nums1[i]){
                    number = nums2[j];
                    break;
                }
            }
            ans.push_back(number);
        }
        return ans;
    }
    
    //////////////////////////////////////////////////////////////////////////
    // use monotonic stack to store next greater
    // https://labuladong.gitbook.io/algo-en/ii.-data-structure/monotonicstack
    // O(n) time
    // O(m) space
    //////////////////////////////////////////////////////////////////////////
    
    std::unordered_map<Index, int> next_greater;
    void populateNextGreater(const vector<int>& nums) {
        std::vector<int> stack;
        for (int i = nums.size()-1; i>=0; i--) {
            while (!stack.empty() && stack.back() <= nums[i]) {
                stack.pop_back();
            }
            next_greater[i] = (stack.empty() ? -1 : stack.back());
            stack.push_back(nums[i]);
        }
    }
    
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        for (int i = nums2.size()-1; i>=0; i--) {
            earliest[nums2[i]] = i;
        }
        populateNextGreater(nums2);
        
        vector<int> ans;
        for (int i=0; i<nums1.size(); i++) {
            if (earliest.find(nums1[i]) == earliest.end()) {
                ans.push_back(-1);
                continue;
            }
            ans.push_back(next_greater[earliest[nums1[i]]]);    
        }
        return ans;
    }
};
