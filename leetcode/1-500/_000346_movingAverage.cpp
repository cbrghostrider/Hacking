class MovingAverage {
    std::deque<int> window;
    int window_size = 0;
    double window_sum = 0;
public:
    MovingAverage(int size) {
        window_size = size;
    }
    
    double next(int val) {
        window.push_back(val);
        window_sum += val;
        if (window.size() > window_size) {
            window_sum -= window.front();
            window.pop_front();
        }
        return (window_sum / window.size());
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
