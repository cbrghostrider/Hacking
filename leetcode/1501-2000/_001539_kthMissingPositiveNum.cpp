class Solution {
public:
    int bruteForce(const vector<int>& arr, int k) {
        int num_missing = 0;
        int lastChecked = 0;
        for (const int val: arr) {
            int new_missing = val - lastChecked - 1;
            if (num_missing + new_missing < k) {
                num_missing += new_missing;
                lastChecked = val;
                continue;
            }
            return lastChecked + (k - num_missing);
        }
        return arr[arr.size() - 1] + (k - num_missing);
    }
    
    int nlogn(const vector<int>& arr, int k, int left, int right) {
        if (right - left <= 1) {
            int num_missing_left = arr[left] - left - 1;
            int num_missing_right = arr[right] - right - 1;
            if (num_missing_left >= k) {
                return k;
            } else if (num_missing_right < k) {
                return arr[right] + (k - num_missing_right);
            }
            return arr[left] + (k - num_missing_left);
        }
        
        int mid = ((long long)left + right) / 2;
        int missing_mid = arr[mid] - mid - 1;
        
        if (missing_mid < k) {
            return nlogn(arr, k, mid, right);
        }
        return nlogn(arr, k, left, mid);
    }
    
    int findKthPositive(vector<int>& arr, int k) { 
        return nlogn(arr, k, 0, arr.size()-1);
    }
};
