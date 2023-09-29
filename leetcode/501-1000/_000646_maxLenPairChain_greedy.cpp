class Solution {
  public:
    // O(n log n) for time, O(1) for space.
    int findLongestChain(vector<vector<int>>& pairs) {
        std::sort(pairs.begin(), pairs.end(), [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[1] != rhs[1]) return lhs[1] < rhs[1];
            return lhs[0] < rhs[0];
        });
        
        int chain=0;
        int last_end = -1005;
        for (int i=0; i<pairs.size(); i++) {
            if (pairs[i][0] > last_end) {
                last_end = pairs[i][1];
                chain++;
            }
        }
        return chain;
    }
}
