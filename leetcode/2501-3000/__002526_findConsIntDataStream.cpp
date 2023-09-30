class DataStream {
    std::priority_queue<int, vector<int>, std::greater<int>> pq;
    int value_;
    int k_;
    int tstamp_=0;
public:
    DataStream(int value, int k) : value_(value), k_(k) {
        
    }
    
    bool consec(int num) {
        tstamp_++;

        // If need be, record this timestamp.
        if (num == value_) {
            pq.push(tstamp_);
        }

        // Purge old timestamps.
        int check_ts = tstamp_ - k_;
        while (!pq.empty() && pq.top() <= check_ts) {
            pq.pop();
        }

        return (pq.size() == k_);
    }
};

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */
