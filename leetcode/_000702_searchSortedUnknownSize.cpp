/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {
public:
    // Perform open-ended binary search.
    int search(const ArrayReader& reader, int target) {
        int last = 0, index = 0, step = 1;
        const int INVALID = (0x1 << 31) - 1;
        while (1) {
            int iter = 0;
            while (reader.get(index) < target && reader.get(index) != INVALID) {
                iter++;
                last = index;
                index += step;
                step *= 2;
            }
            if (reader.get(index) == target) {
                return index;
            }
            if (iter < 2) {
                return -1;
            }
            step = 1;
            index = last;
        }
        return -1;
    }
};
