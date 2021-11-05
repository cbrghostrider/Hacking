class Solution {
    using MinHeap = std::priority_queue<int, vector<int>, std::greater<int>>;
    unordered_map<int, MinHeap> scores;
public:
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        for (const auto& item : items) {
            const int& id = item[0];
            const int& score = item[1];
            scores[id].push(score);
            if (scores[id].size() > 5) {scores[id].pop();}
        }
        vector<vector<int>> ans;
        for (auto& kv : scores) {
            const int& id = kv.first;
            int sum = 0;
            while (kv.second.size() > 0) {
                sum += kv.second.top();
                kv.second.pop();
            }
            ans.push_back({id, sum/5});
        }
        std::sort(ans.begin(), ans.end(), [](const vector<int>& left, const vector<int>& right) {
            return (left[0] < right [0]);
        });
        return ans;
    }
};
