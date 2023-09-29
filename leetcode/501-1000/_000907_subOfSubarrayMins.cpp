class Solution {
public:
    
    // O(n) time, O(n) space.
    // Monotonic stacks to the rescue!
    int sumSubarrayMins(vector<int>& arr) {
        // prev and next lesser elements (and their indices)
        vector<pair<int, int>> ple, nle; 
        
        // (num_lhs, num_rhs)
        // for index i, num of elem to the ple and nle on lhs and rhs respectively
        vector<pair<int, int>> sizes(arr.size(), {0, 0});
        
        for (int i=0; i<arr.size(); i++) {
            while (!ple.empty() && ple.back().first >= arr[i]) {
                ple.pop_back();
            }
            sizes[i].first = ple.empty() ? i : i - ple.back().second - 1;
            ple.push_back({arr[i], i});
        }
        
        for (int i=arr.size()-1; i>=0; i--) {
            while (!nle.empty() && nle.back().first > arr[i]) {
                nle.pop_back();
            }
            sizes[i].second = nle.empty() ? arr.size() - 1 - i : nle.back().second - i - 1;
            nle.push_back({arr[i], i});
        }
        
        long msum=0;
        for (int i=0; i<sizes.size(); i++) {
            msum += arr[i];
            msum %= 1000000007;
            int lhs_num = sizes[i].first;
            int rhs_num = sizes[i].second;
            msum += arr[i] * lhs_num;  // for each subset on the lhs
            msum %= 1000000007;
            msum += arr[i] * rhs_num;  // for each subset on the rhs
            msum %= 1000000007;
            msum += (long)arr[i] * lhs_num * rhs_num;  // for cross subsets
            msum %= 1000000007;                        
        }
        return msum;
    }
}
