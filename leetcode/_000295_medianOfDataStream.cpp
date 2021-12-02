class MedianFinder {
    std::priority_queue<int, vector<int>, std::less<int>> max_heap;     // for left half numbers
    std::priority_queue<int, vector<int>, std::greater<int>> min_heap;  // for right half numbers
public:
    MedianFinder() {}
    
    // O(log n) time.
    void addNum(int num) {
        if (max_heap.size()==0 && min_heap.size() == 0) {
            max_heap.push(num);
            return;
        }
        if (num < max_heap.top()) { // guaranteed to exist now, since something was inserted there on first number
                                    // we don't remove numbers from the MedianFinder as a whole, so it will stay >=1 size
            if (max_heap.size() <= min_heap.size()) {
                max_heap.push(num);
                return;
            }
            int move = max_heap.top();
            max_heap.pop();
            min_heap.push(move);
            max_heap.push(num);
        } else if (min_heap.empty() || num > min_heap.top()) {
            if (min_heap.size() <= max_heap.size()) {
                min_heap.push(num);
                return;
            }
            int move = min_heap.top();
            min_heap.pop();
            max_heap.push(move);
            min_heap.push(num);
        } else {
            if (max_heap.size() <= min_heap.size()) {
                max_heap.push(num);
            } else {
                min_heap.push(num);
            }
        }
    }
   
    // O(1) time. 
    double findMedian() {
        if (max_heap.size() > min_heap.size()) return max_heap.top();
        if (min_heap.size() > max_heap.size()) return min_heap.top();
        return ((max_heap.top() + min_heap.top()) / 2.0);
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
