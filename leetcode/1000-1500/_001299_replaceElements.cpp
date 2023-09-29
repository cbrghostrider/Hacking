class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int greatest = arr[arr.size()-1];
        for (int i=arr.size()-2; i>=0; i--) {
            int temp = arr[i];
            arr[i] = greatest;
            if (temp > greatest) greatest = temp;
        }
        arr[arr.size()-1] = -1;
        return arr;
    }
};
