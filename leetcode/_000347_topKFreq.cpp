struct Comp {
    Comp() {}
    bool operator()(int lhs, int rhs) {
        if (freqs[lhs] != freqs[rhs]) {return freqs[lhs] < freqs[rhs];}
        return lhs > rhs;            
    }
    static unordered_map<int, int> freqs;
};

unordered_map<int, int> Comp::freqs;

class Solution {
public:
    // O(n log n) time, O(n) space.
    vector<int> topKFrequent_(vector<int>& nums, int k) {
        unordered_map<int, int> freqs;
        for (int n : nums) {freqs[n]++;}
        vector<int> ans;
        for (const auto& kv : freqs) {ans.push_back(kv.first);}
        std::sort(ans.begin(), ans.end(), [&freqs](int lhs, int rhs) -> bool {
            if (freqs[lhs] != freqs[rhs]) {return freqs[lhs] > freqs[rhs];}
            return lhs < rhs;
        });
        if (ans.size() > k) ans.erase(begin(ans)+k, ans.end());
        return ans;
    }
    
    // O(n log n) time, O(n) space.
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int>& freqs  = Comp::freqs;
        for (int n : nums) {freqs[n]++;}
        
        std::priority_queue<int, vector<int>, Comp> heap;
        for (const auto& kv : freqs) {heap.push(kv.first);}
        
        vector<int> ans;
        for (int i=0; i<k && !heap.empty(); i++) {
            ans.push_back(heap.top());
            heap.pop();
        }
        return ans;
    }

};


