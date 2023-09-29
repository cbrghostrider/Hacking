class StockPrice {
    struct Info {
        int timestamp=0;
        int price=0;
        int tag=0;
    };
    function<bool(const Info&, const Info&)> minComp = [](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.price != rhs.price) {return lhs.price > rhs.price;}
        return lhs.tag < rhs.tag;
    };
    function<bool(const Info&, const Info&)> maxComp = [](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.price != rhs.price) {return lhs.price < rhs.price;}
        return lhs.tag < rhs.tag;
    };
    using MinHeap=priority_queue<Info, vector<Info>, decltype(minComp)>;
    using MaxHeap=priority_queue<Info, vector<Info>, decltype(maxComp)>;
    
    MinHeap min_heap;
    MaxHeap max_heap;
        
    unordered_map<int, int> tstamp_to_tag;
    int latest=0;
    int time=0;
    
public:
    StockPrice() {
        min_heap = MinHeap(minComp);
        max_heap = MaxHeap(maxComp);
    }
    
    void update(int timestamp, int price) {
        if (timestamp >= time) {
            latest = price;
            time = timestamp;
        }
        Info info = {timestamp, price, ++tstamp_to_tag[timestamp]};
        min_heap.push(info);
        max_heap.push(info);
    }
    
    int current() {
        return latest;
    }
    
    int maximum() {
        while (!max_heap.empty()) {
            auto elem = max_heap.top(); max_heap.pop();
            int latest_tag = tstamp_to_tag[elem.timestamp];
            if (elem.tag == latest_tag) {
                max_heap.push(elem);
                break;
            }            
        }
        return max_heap.top().price;        
    }
    
    int minimum() {
        while (!min_heap.empty()) {
            auto elem = min_heap.top(); min_heap.pop();
            int latest_tag = tstamp_to_tag[elem.timestamp];
            if (elem.tag == latest_tag) {
                min_heap.push(elem);
                break;
            }            
        }
        return min_heap.top().price;        
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
