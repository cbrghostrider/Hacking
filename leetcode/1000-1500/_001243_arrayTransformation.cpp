class Solution {
public:
    vector<int> transformArray(vector<int>& arr) {
        vector<int> work = arr;
        bool changed = true;
        while (changed) {
            changed = false;
            work[0] = arr[0];
            work[arr.size()-1] = arr[arr.size()-1];
            for (int i=1; i<arr.size()-1; i++) {
                int val = arr[i];
                if (val < arr[i-1] && val < arr[i+1]) {
                    work[i] = val+1;
                    changed = true;
                } else if (val > arr[i-1] && val > arr[i+1]) {
                    work[i] = val-1;
                    changed = true;
                } else {
                    work[i] = val;
                }
            }
            arr = work;
        }
        return arr;
    }
};
