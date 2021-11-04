class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        if (arr.size()<3) return false;
        if (arr[0] > arr[1]) return false;
        if (arr[arr.size()-2] < arr[arr.size()-1]) return false;

        bool check_inc = true;
        for (int i=1; i<arr.size(); i++) {
            if (check_inc) {
                if (arr[i] < arr[i-1]) { check_inc = false; }
                else if (arr[i] == arr[i-1]) return false;
            } else {
                if (arr[i] >= arr[i-1]) return false;
            }
        }
        return true;
    }
};
