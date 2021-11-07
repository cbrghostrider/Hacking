class Solution {
public:
    double average(vector<int>& salary) {
        int min = std::numeric_limits<int>::max();
        int max = std::numeric_limits<int>::min();
        for (int s : salary) {
            if (s < min) {
                min = s;
            }
            if (s > max) {
                max = s;
            }
        }
        double sum = 0;
        int count = 0;
        for (int s : salary) {
            if (s == min || s == max) continue;
            sum += s;
            count++;
        }
        return (count == 0 ? 0 : sum/count);
    }
};
