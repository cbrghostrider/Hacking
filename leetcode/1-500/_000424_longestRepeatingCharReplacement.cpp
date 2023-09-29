class Solution {    
    struct Info {
        int version;
        char ch;
        int count;
    };
    
    vector<int> versions;
    std::function<bool(const Info&, const Info&)> comp = 
        [](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.count != rhs.count) return lhs.count < rhs.count;
        return lhs.version < rhs.version;
    };
    using MaxHeap = priority_queue<Info, vector<Info>, decltype(comp)>;
    MaxHeap heap;
    unordered_map<char, int> counts;
    
    void normalizeHeap() {
        while (!heap.empty() && heap.top().version < versions[heap.top().ch - 'A']) {
            heap.pop();
        }
    }
    
    void updateHeap(char ch, int count) {
        normalizeHeap();
        int version = ++versions[ch-'A'];
        heap.push({version, ch, count});
    }
    
    bool isEmptyHeap() {
        normalizeHeap();
        return heap.empty();
    }
    
    // does not do checking
    Info topHeap() {
        normalizeHeap();
        return heap.top();
    }
    
public:    
    // k refers to k "individual" letter replacements (may be same letter), 
    // not k sets of unique letters!
    //
    // Unfortunately this solution turned out to be uglier than I thought...
    //
    // Some of the complexity comes from "versioning" the heap.
    // i.e. I need a heap with "update" possible for elements.
    // but since the interface does not support updates, I had to implement my own
    // versioning on top of it.
    // Basically, we keep a "latest version" value in the versions array.
    // And any time the top of heap isn't the latest version, we just pop it and ignore.
    // See normalizeHeap() function.
    //
    // Also the final else-if clause could use some improvement.
    // Essentially it needs to do a "re-init" step at one point, which can be handled
    // more elegantly, perhaps via simple refactoring of it into a function.
    int characterReplacement(string s, int k) {
        if (s.size() <= 1 || k >= s.size()-1) return s.size();
        versions = vector<int>(26, 0);
        heap = MaxHeap(comp);
        
        int max_len=1;  // the length of the longest substring detected so far.
        int left=0, right=1;
        counts[s[left]]++;
        updateHeap(s[left], counts[s[left]]);
        
        auto updateMax = [&left, &right, &max_len]() {
            int running_len = right-left+1;
            if (running_len > max_len) {max_len = running_len;}
        };
        
        while (left < s.size()) {
            Info th = topHeap();
            
            if (right < s.size() && counts.find(s[right]) != counts.end() && th.ch == s[right]) {
                // right ptr is same letter as max freq in current window
                counts[s[right]]++;
                updateHeap(s[right], counts[s[right]]);
                updateMax();
                right++;                
            } else if (right < s.size() && (right-left+1-th.count) <= k) {
                // right ptr is different letter than max freq, but 
                // we still have replacements available
                counts[s[right]]++;
                updateHeap(s[right], counts[s[right]]);
                updateMax();
                right++;                
            } else if (left < s.size()) {
                counts[s[left]]--;
                updateHeap(s[left], counts[s[left]]);
                if (counts[s[left]] == 0) {counts.erase(s[left]);}
                left++;
                if (left == right && left != s.size()) {
                    versions = vector<int>(26, 0);
                    MaxHeap new_heap(comp);
                    std::swap(heap, new_heap);
                    counts[s[left]]++;
                    updateHeap(s[left], counts[s[left]]);
                    right = left+1;
                }
            }                                        
        }
        return max_len;
    }
};
