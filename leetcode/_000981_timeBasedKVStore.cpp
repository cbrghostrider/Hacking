class TimeMap {
    using TimeStamp = int;
    using TSVal = pair<TimeStamp, string>;
    using TSStore = vector<TSVal>;
    unordered_map<string, TSStore> cont;
    
    string search(const TSStore& store, int left, int right, TimeStamp leq_me) {
        if (left == right) {
            if (store[left].first <= leq_me) return store[left].second;
            return "";
        }
        if (left + 1 == right) {
            if (store[right].first <= leq_me) return store[right].second;
            if (store[left].first <= leq_me) return store[left].second;
            return "";
        }
        int mid = (left+right)/2;
        if (store[mid].first <= leq_me) {
            return search(store, mid, right, leq_me);
        }
        return search(store, left, mid, leq_me);
    }
    
public:
    TimeMap() {}
    
    // O(1) time.
    void set(string key, string value, int timestamp) {
        cont[key].push_back(make_pair(timestamp, value));
    }
    
    // O(log n) time.
    string get(string key, int timestamp) {
        if (cont[key].size() == 0) return "";
        return search(cont[key], 0, cont[key].size()-1, timestamp);
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
