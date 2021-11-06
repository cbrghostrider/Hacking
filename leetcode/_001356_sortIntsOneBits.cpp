class Solution {
    int num_ones(int num) {
        unsigned int mask = 0x1;
        unsigned int unum = static_cast<unsigned int>(num);
        int count = 0;
        while (unum) {
            if (unum & mask) count++;
            unum = (unum >> 1);
        }
        return count;
    }
public:
    vector<int> sortByBits(vector<int>& arr) {
        std::sort(arr.begin(), arr.end(), [this](int left, int right) -> bool {
            int bits_left = num_ones(left);
            int bits_right = num_ones(right);
            if (bits_left != bits_right) {
                return bits_left < bits_right;
            }
            return left < right;
        });
        return arr;
    }
};
