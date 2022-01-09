class Solution {
public:
    
    // Runtime is: (n/k * (log n + k + k log n))
    // n/k is the number of times the while loop runs
    // log n is the time to find the initial map.begin()
    // k is the time to walk the tree for consecutive elements
    // k log n is the time to perform up to k erases on the tree
    //
    // Basically: O(n log n)
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        map<int, int> freq;
        for (int n : hand) { freq[n]++; }
        
        while (!freq.empty()) {
            unordered_set<int> purge;
                        
            auto it = freq.begin();
            int last=it->first;
            auto check = [&purge, &freq](int& last) {                
                freq[last]--;
                if (freq[last] == 0) {
                    purge.insert(last);                
                }                
            };
            check(last);
            
            for (int i=1; i<groupSize; i++) {            
                it++;
                if (it == freq.end()) return false;
                if (it->first != last+1) return false;
                
                last = it->first;
                check(last);
            }
            
            for (int i : purge) {
                freq.erase(i);
            }
        }
        return true;
    }
};
