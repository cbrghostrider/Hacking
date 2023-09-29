class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int max = 0;
        int val = 0;
        for (int alt : gain) {
            val += alt;
            if (val > max) max = val;
        }
        return max;
    }
};
