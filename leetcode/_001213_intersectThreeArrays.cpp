class Solution {
public:
    // Binary searches arr for num, within indices [left,right], and returns true if found.
    bool foundIn(const vector<int>& arr, int num, int left, int right) {
        if (right - left <= 1) {
            if (arr[right] == num || arr[left] == num) {
                return true;
            }
            return false;
        }
        int mid = ((long long) left + right) / 2;
        if (arr[mid] == num) {
            return true;
        } else if (arr[mid] < num) {
            return foundIn(arr, num, mid+1, right);
        }
        return foundIn(arr, num, left, mid-1);
    }
    
    vector<int> intersect(const vector<int>& arr1, const vector<int>& arr2) {
        vector<int> result;
        for (const int val : arr1) {
            if (foundIn(arr2, val, 0, arr2.size()-1)) {
                result.push_back(val);
            }
        }
        return result;
    }
    
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        vector<int> inter = intersect(arr1, arr2);
        return intersect(inter, arr3);
    }
};
