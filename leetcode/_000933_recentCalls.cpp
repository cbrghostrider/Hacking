class RecentCounter {
    std::priority_queue<int, vector<int>, std::greater<int>> min_heap;
public:
    RecentCounter() {}
    
    int ping(int t) {
        while (!min_heap.empty() && min_heap.top() < t-3000) { min_heap.pop();}
        min_heap.push(t);    
        return min_heap.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
