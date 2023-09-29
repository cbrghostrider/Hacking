class Solution {
    bool compare(const string& num1, const string& num2) {
        if (num1.size() != num2.size()) {
            return num1.size() > num2.size();
        }
        for (int i=0; i<num1.size(); i++) {
            if (num1[i] != num2[i]) {return num1[i] > num2[i];}
        }
        return false;
    }
public:
    // O(n log n) time.
    string kthLargestNumber(vector<string>& nums, int k) {
        if (k <= 0 || k > nums.size()) return "";
        k -= 1;  // make it 0-indexed
        std::sort(nums.begin(), nums.end(), 
                  [this](const string& lhs, const string& rhs) -> bool { 
            return compare(lhs, rhs);
        });
        return nums[k];
    }
};
