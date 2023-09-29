class Solution {
    bool matches(const vector<int>& arr, int m, int p1, int p2) {
        int i=0;
        for (; i<m && p2 < arr.size(); i++) {
            if (arr[p1++] != arr[p2++]) return false;
        }
        return (i == m);
    }
    
    // checks if pattern of length m starting at start, is repeated k-1 times after start+m;
    bool isRepeatedEnough(const vector<int>& arr, int m, int k, int start) {
        if (arr.size() - start < m*k) return false;
        int remaining = k-1;
        for (int p=start+m; p<arr.size() && remaining > 0;) {
            if (matches(arr, m, start, p)) {
                remaining--;
            } else {
                break;
            }
            p += m;
        }
        return (remaining == 0);
    }
    
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        for (int i=0; i<arr.size(); i++) {
            if (isRepeatedEnough(arr, m, k, i)) return true;
        }
        return false;
    }
};
