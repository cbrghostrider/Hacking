class Solution {
public:
    int missingNumber(vector<int>& arr) {
        int diff_10 = arr[1] - arr[0];
        int diff_21 = arr[2] - arr[1];
        if (diff_10 == 2*diff_21) {
            return arr[0] + diff_21;
        } else if (diff_10 *2 == diff_21) {
            return arr[1] + diff_10;
        }
        
        for (int i=3; i<arr.size(); i++) {
            int last_diff = arr[i] - arr[i-1];
            if (last_diff == 2 * diff_10) {
                return arr[i-1] + diff_10;
            }
        }
        return -1;  // should not happen
    }
};
