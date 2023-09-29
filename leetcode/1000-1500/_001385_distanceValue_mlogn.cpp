class Solution {
public:
    // finds if val is a valid distance value for elems, using binary search.
    bool isDistanceValue(const vector<int>& elems, int left, int right, int val, int d) {
        if (right - left <= 1) {
            if (abs(val - elems[left]) <= d) {
                return false;
            }
            if (abs(val - elems[right]) <= d) {
                return false;
            }
            return true;
        }
        
        int mid = ((long long)left + right) / 2;
        if (abs(val - elems[mid]) <= d || abs(val - elems[mid-1]) <= d || abs(val - elems[mid+1]) <= d) {
            return false;
        } else if (elems[mid] > val) {
            return isDistanceValue(elems, left, mid-1, val, d);
        }
        return isDistanceValue(elems, mid+1, right, val, d);
    }
    
    // O(mlogn + nlogn) solution
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        std::sort(arr2.begin(), arr2.end());
        int result = 0;
        for (const int val : arr1) {
            if (isDistanceValue(arr2, 0, arr2.size() - 1, val, d)) {
                result++;
            }
        }
        return result;
    }
};
