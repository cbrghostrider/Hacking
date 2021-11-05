class Solution {
    std::priority_queue<int, vector<int>, std::greater<int>> min_heap;
    std::priority_queue<int, vector<int>, std::less<int>> max_heap;
        
public:
    // O(n) time, O(n) space.
    double trimMean(vector<int>& arr) {
        const int remove = arr.size() * 5 / 100;
        double sum = 0;
        for (int i=0; i<arr.size(); i++) {
            sum += arr[i];
            
            if (min_heap.size() < remove) {
                min_heap.push(arr[i]);
            } else if (arr[i] > min_heap.top()) {
                min_heap.pop();
                min_heap.push(arr[i]);
            }
            
            if (max_heap.size() < remove) {
                max_heap.push(arr[i]);
            } else if (arr[i] < max_heap.top()) {
                max_heap.pop();
                max_heap.push(arr[i]);
            }
        }
        
        int sum_min = 0, sum_max = 0;
        while (!min_heap.empty()) {
            sum_min += min_heap.top();
            min_heap.pop();
        }
        while (!max_heap.empty()) {
            sum_max += max_heap.top();
            max_heap.pop();
        }
        sum = sum - sum_min - sum_max;
        double mean = sum / (arr.size() - 2*remove);
        return mean;
    }
};
