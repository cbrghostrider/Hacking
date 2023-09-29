class Solution {
public:
    // O(n log n)
    vector<int> sortTransformedArray_(vector<int>& nums, int a, int b, int c) {
        for (int& x : nums) {
            x = a*x*x + b*x + c;
        } 
        std::sort(nums.begin(), nums.end());
        return nums;
    }
   
    // bleh... just messing around here... 
    // c = width of range of nums = constant
    // O(n + c log c)
    // O(n) since c is constant here
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        vector<int> all_xforms;
        for (int i=-100; i<=100; i++) {
            all_xforms.push_back(a*i*i + b*i + c);
        }
        
        std::sort(all_xforms.begin(), all_xforms.end());
        auto it = std::unique(all_xforms.begin(), all_xforms.end());
        all_xforms.erase(it, all_xforms.end());
        
        unordered_map<int, int> counts;
        for (int x : all_xforms) {counts[x] = 0;}
        
        for (int n : nums) {
            int x = a*n*n + b*n + c;
            counts[x]++;
        }
        
        vector<int> ans;
        for (int x : all_xforms) {
            int count = counts[x];
            for (int i=0; i<count; i++) {
                ans.push_back(x);
            }            
        }
        return ans;
    }
};
