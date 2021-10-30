class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long m1, m2, m3;
        m1 = m2 = m3 = std::numeric_limits<long>::min();
        for (int n : nums) {
            if (n > m1) {
                m3 = m2;
                m2 = m1;
                m1 = n;
            } else if (n > m2 && n != m1) {
                m3 = m2;
                m2 = n;
            } else if (n > m3 && n != m1 && n != m2) {
                m3 = n;
            }       
        }
        return (m3 == std::numeric_limits<long>::min() ? m1 : m3);
    }
};
