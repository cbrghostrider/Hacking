class Solution {
    vector<int> cumu_sum;
public:
    // O(n^2) solution.
    int sumOddLengthSubarrays(vector<int>& arr) {
        int sum = 0;
        for (int i=0; i<arr.size(); i++) {
            sum += arr[i];
            cumu_sum.push_back(sum);
        }
        
        sum = 0;
        for (int start=0; start<arr.size(); start++) {
            for (int sz=1; sz<=arr.size(); sz+=2) {
                int end = start+sz-1;
                if (end >= arr.size()) break;
                int arr_sum = cumu_sum[end] - cumu_sum[start] + arr[start];
                sum += arr_sum;
            }
        }
        return sum;
    }
};
