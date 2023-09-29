class Solution {
    std::priority_queue<int, vector<int>, std::less<int>> max_heap;
public:
    int lastStoneWeight(vector<int>& stones) {
        for (int s : stones) {max_heap.push(s);}
        
        while (max_heap.size() >= 2) {
            int s1 = max_heap.top();
            max_heap.pop();
            int s2 = max_heap.top();
            max_heap.pop();
            if (s1 != s2) {max_heap.push(s1 - s2);}
        }
        
        return (max_heap.size() == 1 ? max_heap.top() : 0);
    }
};
