class MyCalendarThree {
    struct Info {
        int val=-1;   // the start/end value
        bool is_start = true;  // whether the value corresponds to start or end
        bool operator<(const Info& rhs) const {
            if (val != rhs.val) return val < rhs.val;
            if (is_start != rhs.is_start) {
                return (is_start ? false : true);
            }
            return false;
        }
        bool operator==(const Info& rhs) const {
            return (val == rhs.val && is_start == rhs.is_start);
        }
    };
    
    std::multiset<Info> tree;
    using Iter=std::multiset<Info>::iterator;
    int max_k_booking=0;
    
    void insert(int val, bool flag) {
        Info info = {val, flag};
        tree.insert(info);
    }
    
    // count how many intervals are open when we reach start
    pair<int, Iter> countOpens(int query) {        
        int count=0;
        Iter it = tree.begin();
        for (; it != tree.end(); it++) {
            if (it->val == query && it->is_start) {
                break;
            }      
            if (it->is_start) {count++;} else {count--;}
        }
        return make_pair(count, it);
    }
    
    int query(int start, int end) {
        auto prior = countOpens(start);
        Iter it = prior.second;
        int count=prior.first;
        int max_count=count;
        for (; it != tree.end(); it++) {
            if (it->val == end && !it->is_start) {
                break;
            }
            if (it->is_start) {count++;} else {count--;}
            if (count > max_count) {max_count = count;}
        }
        return max_count;
    }
    
public:
    MyCalendarThree() {
        
    }
    
    // O(n^2) time, O(n) space.
    int book(int start, int end) {
        insert(start, true);
        insert(end, false);
        int new_k_booking = query(start, end);
        max_k_booking=std::max(max_k_booking, new_k_booking);
        return max_k_booking;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */
