class Solution {
    using MinHeap=std::priority_queue<int, vector<int>, std::greater<int>>;
    
public:
    // Start filling from the most freq letter to the least freq.
    // Fill all the even indices first, then fill all the odd indices.
    // If at any point, you don't have an index left to fill, or your adjacent thing
    // is the same as you, then return "".
    string reorganizeString(string s) {
        MinHeap odds, evens;
        map<char, int> freqs;
        
        for (int i=0; i<s.size(); i++) {
            if (i%2 == 0) {evens.push(i);} else {odds.push(i);}
            freqs[s[i]]++;
        }
        
        vector<pair<char, int>> counts;
        for (const auto& kv : freqs) {counts.push_back({kv.first, kv.second});}
        std::sort(counts.begin(), counts.end(), 
                  [](const pair<char, int>& lhs, const pair<char, int>& rhs) -> bool {
            if (lhs.second != rhs.second) return lhs.second > rhs.second;
            return lhs.first < rhs.first;
        });
        
        string ans(s.size(), ' ');
        
        for (const auto& kv : counts) {
            if (odds.empty() && evens.empty()) return "";
            MinHeap* heap = (evens.empty() ? &odds : &evens);
            char ch = kv.first;
            int count = kv.second;
            while (count) {
                if (heap->empty()) {
                    if (odds.empty()) return "";
                    heap = &odds;
                }
                int index = heap->top();
                ans[heap->top()] = ch;
                if (index != 0 && ans[index-1] == ch) return "";
                if (index != s.size()-1 && ans[index+1] == ch) return "";
                heap->pop();
                count--;
            }
        }
        
        return ans;
    }
};
