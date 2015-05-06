class Solution {
private:
    map<int, int> numMap_; //(number, how many times it occurred)
public:
    int singleNumber(vector<int>& nums) {
        for (const int& num : nums) {
            if (numMap_.find(num) != numMap_.end()) {
                numMap_[num] += 1;
            } else {
                numMap_[num] = 1;
            }
        }
        for (const int& num : nums) {
            if (numMap_[num] == 1) {
                return num;
            }
        }
        return -1; //ill-defined problem
    }
};
