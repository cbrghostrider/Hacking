class Solution {
    unordered_map<int, int> countFreq_; //(number, count)
public:
    int singleNumber(vector<int>& nums) {
        for (int& num : nums) {
            if (countFreq_.find(num) == countFreq_.end()) {
                countFreq_[num] = 1;
            } else {
                countFreq_[num] += 1;
            }
        }
        for (int & num : nums) {
            if (countFreq_[num] == 1) {
                return num;
            }
        }
        return -1;//ill-defined input
    }
};
