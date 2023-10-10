class Solution {
    // Key: value in nums.
    // Value: list of indices of this key in nums.
    unordered_map<int, vector<int>> val_indices;
public:
    vector<long long> distance(vector<int>& nums) {
        for (int i=0;i<nums.size(); i++) {
            val_indices[nums[i]].push_back(i);
        }

        vector<long long> ans(nums.size(), 0);
        for (auto& kv : val_indices) {
            int key = kv.first;
            auto& val = kv.second;
            long long rsum = 0, lsum = 0;
            int rnum=val.size(), lnum=0;

            std::for_each(val.begin(), val.end(), [&rsum](int v) {
                rsum += v;
            });

            for (int i=0; i<val.size(); i++) {
                long long ind = val[i];

                long long my_ans = rsum - rnum*ind;
                my_ans += lnum*ind - lsum;
                ans[ind] = my_ans;

                rsum -= ind; rnum -= 1;
                lsum += ind; lnum += 1;
            }
        }
        return ans;
    }
};
