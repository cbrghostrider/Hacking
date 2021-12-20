class Solution {
    vector<int> leaders;
    vector<int> sizes;
    
    int uf_find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
    void uf_union(int leader1, int leader2) {
        if (leader1 == leader2) return;
        if (sizes[leader1] < sizes[leader2]) {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];
        } else {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];            
        }
    }
    
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        
        for (int i=0; i<s.size(); i++) {
            leaders.push_back(i);
            sizes.push_back(1);
        }
        
        for (int i=0; i<pairs.size(); i++) {
            int leader1 = uf_find(pairs[i][0]);
            int leader2 = uf_find(pairs[i][1]);
            uf_union(leader1, leader2);
        }
        
        unordered_map<int, unordered_set<int>> reachable;
        
        for (int i=0; i<leaders.size(); i++) {
            int leader = uf_find(i);
            reachable[leader].insert(i);
        }
        
        for (int i=0; i<s.size(); i++) {
            int leader = uf_find(i);
            if (sizes[leader] == 1) continue;  // nothing to swap to
            
            int min_index=i;
            for (int ind : reachable[leader]) {
                if (ind < i) continue;  // already handled
                
                if (s[ind] < s[min_index]) {
                    min_index = ind;
                }
            }
            if (min_index != i) {
                std::swap(s[min_index], s[i]);
            }
            reachable[leader].erase(i);
        }
        return s;
    }
};
