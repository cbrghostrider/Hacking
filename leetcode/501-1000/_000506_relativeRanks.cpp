class Solution {
    std::unordered_map<int, string> ranks;
    std::priority_queue<int, std::vector<int>, std::less<int>> max_heap;
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        for (int s : score) { max_heap.push(s); }
        int rank = 1;
        while (!max_heap.empty()) {
            int s = max_heap.top();
            max_heap.pop();
                        
            switch (rank) {
                case 1:
                    ranks[s] = "Gold Medal";
                    break;
                case 2:
                    ranks[s] = "Silver Medal";
                    break;
                case 3:
                    ranks[s] = "Bronze Medal";
                    break;
                default:
                    ranks[s] = std::to_string(rank);
            } 
            rank++;
        }
        vector<string> ans;
        for (int s : score) {
            ans.push_back(ranks[s]);
        }
        return ans;
    }
};
