class Solution {
public:
    // O(n) time, O(n) space
    // Can optimize away the space by computing cumulative sums on the fly.
    bool canThreePartsEqualSum(vector<int>& arr) {
        if (arr.size() < 3) return false;
        
        vector<int> cumulative_fwd(arr.size(), 0);
        vector<int> cumulative_rev(arr.size(), 0);
        int sum = 0;
        for (int i=0; i<arr.size(); i++) {
            sum += arr[i];
            cumulative_fwd[i] = sum;
        }
        sum = 0;
        for (int i=arr.size()-1; i>=0; i--) {
            sum += arr[i];
            cumulative_rev[i] = sum;
        }
        
        if (sum % 3) return false;
        const int each_sum = sum/3;
        
        int fwd_index = 0, rev_index = arr.size()-1;
        while (cumulative_fwd[fwd_index] != each_sum && fwd_index <= rev_index-2) {
            fwd_index++;
        }
        while (cumulative_rev[rev_index] != each_sum && fwd_index <= rev_index-2) {
            rev_index--;
        }
        return (fwd_index <= rev_index-2);
    }
    
    // O(n^2) time, O(n) space: TOO SLOW!
    bool canThreePartsEqualSum2(vector<int>& arr) {
        if (arr.size() < 3) return false;
        
        vector<int> cumulative(arr.size(), 0);
        int sum = 0;
        for (int i=0; i<arr.size(); i++) {
            sum += arr[i];
            cumulative[i] = sum;
        }
        
        for (int end_first=0; end_first <= arr.size()-3; end_first++) {
            for (int end_second = end_first+1; end_second <= arr.size()-2; end_second++) {
                int sum_first = cumulative[end_first];
                int sum_second = cumulative[end_second] - cumulative[end_first];
                int sum_third = cumulative[arr.size()-1] - cumulative[end_second];
                if (sum_first == sum_second && sum_second == sum_third) {
                    return true;
                }
            }
        }
        return false;
    }
};
