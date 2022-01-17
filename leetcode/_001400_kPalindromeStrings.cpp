class Solution {
    
public:
    bool canConstruct(string s, int k) {
        unordered_map<int, int> freqs;
        for (char ch : s)  { freqs[ch]++; }
        
        int odds=0;
        unordered_set<char> remove;
        for (auto& kv : freqs) {
            if (kv.second % 2 != 0) {
                odds++;
                remove.insert(kv.first);
            }
        }
        
        // as long as odds <= k, you can stick the odd man in one each of k strings
        if (odds > k) return false;
        k -= odds;  // create 1-str palindromes from the odds
        
        for (char ch : remove) {
            freqs[ch]--;
            if (freqs[ch] == 0) {freqs.erase(ch);}
        }
        
        int count = 0;
        for (const auto& kv : freqs) {
            count += kv.second;  // create 1-str palindromes from evens
        }
        
        return (count >= k);        
    }
};
