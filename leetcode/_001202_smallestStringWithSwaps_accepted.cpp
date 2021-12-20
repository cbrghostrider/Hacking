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
        
	// Replacing the linear search for min with a MinHeap reduces runtime significantly.
	// This solution is now accepted!
        auto comp = [](const pair<int, char>& lhs, const pair<int, char>& rhs) -> bool {
            if (lhs.second != rhs.second) return lhs.second > rhs.second;
            return lhs.first > rhs.first;
        };
        using MinHeap = priority_queue<pair<int, char>, vector<pair<int, char>>, decltype(comp)>;
        
        unordered_map<int, MinHeap> reachable;
        
        for (int i=0; i<leaders.size(); i++) {
            int leader = uf_find(i);
            if (reachable.find(leader) == reachable.end()) {
                reachable.emplace(leader, MinHeap(comp));
            }
            reachable.find(leader)->second.push({i, s[i]});
        }
        
        for (int i=0; i<s.size(); i++) {
            int leader = uf_find(i);
            if (sizes[leader] == 1) continue;  // nothing to swap to
            
            while (!reachable.find(leader)->second.empty() && 
                   reachable.find(leader)->second.top().first < i) {
                reachable.find(leader)->second.pop();
            }
            auto elem = reachable.find(leader)->second.top();
            reachable.find(leader)->second.pop();
            if (elem.first != i) {
                char ch = s[i];
                std::swap(s[elem.first], s[i]);
                reachable.find(leader)->second.push({elem.first, ch});
            }
            
        }
        return s;
    }
};
