class Solution {
    int K;
    unordered_map<int, set<int>> conflicts;
    vector<vector<int>> groups;

    void populateConflicts(const vector<int>& nums, int k) {
        for (int n : nums) {
            conflicts[n] = {};
        }
        for (int n : nums) {
            if (conflicts.find(n+k) != conflicts.end()) {
                conflicts[n].insert(n+k);
            }
            if (conflicts.find(n-k) != conflicts.end()) {
                conflicts[n].insert(n-k);
            }
        }        
    }

    void groupify(const vector<int>& nums, int k) {
        unordered_set<int> done;
        while (done.size() != nums.size()) {            
            int start=-1;
            for (int n : nums) {            
                if (done.find(n) != done.end()) continue;
                start = n;
                break;
            }
            vector<int> group;
            vector<int> todo;
            todo.push_back(start);            
            while (!todo.empty()) {
                int val = todo.back();
                todo.pop_back();
                done.insert(val);
                group.push_back(val);
                for (int conf : conflicts[val]) {
                    if (done.find(conf) != done.end()) continue;
                    todo.push_back(conf);
                }
            }
            std::sort(group.begin(), group.end());
            groups.push_back(group);
        }
    }

    struct Info {
        long long take=0;  // If this index was taken.
        long long drop=0;  // If this index was dropped.
    };
    // index is index in the group.
    long long compute_group_combos(int index, int k) {
        vector<Info> dp(groups[index].size(), Info());
        dp[0] = {1, 1};  // take that elem, or drop that elem.
        for (int i=1; i<dp.size(); i++) {
            if (groups[index][i] - k != groups[index][i-1]) {
                long long sum = dp[i-1].take + dp[i-1].drop;
                dp[i] = {sum, sum};
                continue;
            }
            // ith elem conflicts with (i-1)th elem
            long long total=0;

            // drop i; then we can take or drop (i-1)
            dp[i].drop = dp[i-1].take + dp[i-1].drop;

            // take i; then we HAVE to drop (i-1)
            if (i-2 >= 0) {
                dp[i].take = dp[i-2].take + dp[i-2].drop;
            } else {
                dp[i].take = 1;
            }

        }
        long long fin = dp.back().take + dp.back().drop;
        return fin;
    }

public:

    long long countTheNumOfKFreeSubsets(vector<int>& nums, int k) {
        K = k;
        std::sort(nums.begin(), nums.end());
        populateConflicts(nums, k);
        groupify(nums, k);
        long long mult=1;
        for (int g=0; g<groups.size(); g++) {
            long long cc = compute_group_combos(g, k);
            mult *= cc;
        }
        return mult;
    }
};
