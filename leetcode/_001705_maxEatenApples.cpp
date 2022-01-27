class Solution {
    struct Info {
        int apples=0  ;         // these many rot on this day
        int expiration=0;       // the expiration day for these apples
    };
    
    function<bool(const Info&, const Info&)> comp = [](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.expiration != rhs.expiration) return lhs.expiration > rhs.expiration;
        return false;
    };
    using MinHeap=priority_queue<Info, vector<Info>, decltype(comp)>;
    
    void discardRotten(MinHeap& min_heap, int cur_day) {
        while (!min_heap.empty() && 
               (min_heap.top().expiration < cur_day || min_heap.top().apples == 0)) {
            min_heap.pop();
        }        
    }
    
    void eatApple(MinHeap& min_heap, int& eaten) {
        if (!min_heap.empty()) {
            eaten++;
            auto elem = min_heap.top(); min_heap.pop();
            elem.apples--;
            if (elem.apples != 0) {min_heap.push(elem);}        
        }
    }
    
public:
    // O(n log n) time, O(n) space.
    int eatenApples(vector<int>& apples, vector<int>& days) {
        MinHeap min_heap(comp);
        int eaten=0;    // how many are eaten so far  
        int i=0;
        
        for (; i<apples.size(); i++) {
            discardRotten(min_heap, i);
            eatApple(min_heap, eaten);
  
            if (apples[i]) {
                int exp = i + days[i];
                min_heap.push({apples[i], exp});
            }
        }
        
        while (!min_heap.empty()) {
            discardRotten(min_heap, i);
            eatApple(min_heap, eaten);
            i++;
        }
        return eaten;
    }
};
