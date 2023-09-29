class Solution {
public:
    // O(nlogn) time, O(n) space
    int maximumPopulation(vector<vector<int>>& logs) {
        std::sort(logs.begin(), logs.end(), [](const vector<int>& left, const vector<int>& right) -> bool {
            if (left[0] != right[0]) return left[0] < right[0];
            return left[1] < right[1];
        });
        std::priority_queue<int, vector<int>, std::greater<int>> min_heap;
        
        int alive = 0;
        int max_alive = 0;
        int year = 0;
        for (const vector<int>& log : logs) {
            while (!min_heap.empty() && min_heap.top() <= log[0]) {
                min_heap.pop();
                alive--;
            }
            min_heap.push(log[1]);
            alive++;
            if (alive > max_alive) {
                max_alive = alive;
                year = log[0];
            }
        }
        return year;
    }
};
