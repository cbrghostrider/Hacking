class Solution {
public:

    // O(n^2) time, O(n) space.
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // We sort people on height (ascending) first, and k (descending) second.
        //
        // Greedy criteria:
        //
        // Take the first of remaining numbers. All the numbers gone before it have been <= it.
        // we will keep track of a ctr, that counts how many before it will be >=
        // Scan positions in ans from the start
        // if unoccupied, it will be later consumed by a greater height, so update counter.
        // if occupied, only update the counter if it already has something equal to current height
        // once counter reaches my position (k) then assign this place to me
        
        std::sort(people.begin(), people.end(),
                  [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[0] != rhs[0]) {return (lhs[0] < rhs[0]);}
            return lhs[1] > rhs[1];
        });
        
        vector<vector<int>> ans(people.size(), vector<int>());
        vector<bool> occupied(people.size(), false);
        
        for (const auto& hk : people) {
            int h = hk[0]; 
            int k = hk[1];
            int ctr=0;
            for (int i=0; i<people.size(); i++) {
                if (ctr == k && occupied[i] == false) {
                    occupied[i] = true;
                    ans[i] = {h, k};
                    break;
                }
                if (occupied[i] == false || ans[i][0] == h) {ctr++;}
            }
        }
        return ans;
    }
};
