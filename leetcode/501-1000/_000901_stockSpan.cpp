class StockSpanner {
    // stores (day, price)
    vector<pair<int, int>> dp_stack;
    int today=0;
public:
    StockSpanner() {}
    
    // O(1) amortized time.
    int next(int price) {
        ++today;
        while (!dp_stack.empty() && dp_stack.back().second <= price) {
            dp_stack.pop_back();
        }
        int ret = dp_stack.empty() ? today - 0 : today - dp_stack.back().first;
        
        dp_stack.push_back({today, price});
        return ret;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
