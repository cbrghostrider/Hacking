class Solution {
public:
    int findGCD(vector<int>& nums) {
        int smallest = std::numeric_limits<int>::max();
        int largest = std::numeric_limits<int>::min();
        for (int n : nums) {
            if (n > largest) largest = n;
            if (n < smallest) smallest = n;
        }
        for (int i=smallest; i>=1; i--) {
            if ((smallest % i == 0) && (largest % i == 0)) return i;
        }
        return 1;
    }
};
