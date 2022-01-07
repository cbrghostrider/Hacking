class HitCounter {
    priority_queue<int, vector<int>, std::greater<int>> min_heap;
    const int WINDOW=300;
    
    void normalize(int cur_time) {
        while (!min_heap.empty() && min_heap.top() <= cur_time-WINDOW) {
            min_heap.pop();
        }
    }
public:
    HitCounter() {}          
    
    void hit(int timestamp) {
        normalize(timestamp);
        min_heap.push(timestamp);        
    }
    
    int getHits(int timestamp) {
        normalize(timestamp);
        return min_heap.size();
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
