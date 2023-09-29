struct UnionFind {
    vector<int> leaders;
    vector<int> sizes;
    vector<bool> infected;
    
    UnionFind(int size) {
        for (int i=0; i<size; i++) {
            leaders.push_back(i);
            sizes.push_back(1);
            infected.push_back(false);
        }
        infected[0] = true;
    }
        
    int uf_find(int index) const {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
    bool is_person_infected(int person) const {
        int leader = uf_find(person);
        return infected[leader];
    }
    
    void mark_person_infected(int person) {
        int leader = uf_find(person);
        infected[leader] = true;
    }
    
    bool is_group_infected(int leader) const {
        return infected[leader];
    }
        
    void uf_union(int leader1, int leader2) {
        if (leader1 == leader2) return;
        if (sizes[leader1] >= sizes[leader2]) {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];
            if (infected[leader2]) {infected[leader1] = true;}
        } else {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];                
            if (infected[leader1]) {infected[leader2] = true;}
        }
    }
    
    vector<int> getInfected() const {
        int group = uf_find(0);  // 0 is definitely infected
        vector<int> ans;
        for (int i=0; i<infected.size(); i++) {
            int my_group = uf_find(i);
            if (my_group == group) {
                ans.push_back(i);
            }
        }
        return ans;
    }    
};

struct Meeting {
    int x=-1;
    int y=-1;
    int time=-1;
};

function<bool(const Meeting&, const Meeting&)> comp = 
    [] (const Meeting& lhs, const Meeting& rhs) -> bool {
    return lhs.time > rhs.time;
};

using MinHeap=priority_queue<Meeting, vector<Meeting>, decltype(comp)>;

class Solution {
    
public:
    // 
    // k = |meetings|
    // O(k log k + n log n) time, O(n + k) space.
    // We put all k meetings in a heap, and pop one by one, hence k log k.
    // We put all people in the UF data structure, and call uf_find, which is n log n total.
    //
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        MinHeap min_heap(comp);
        for (const vector<int>& m : meetings) {
            min_heap.push({m[0], m[1], m[2]});
        }
        
        UnionFind uf(n);
        uf.uf_union(uf.uf_find(0), uf.uf_find(firstPerson));
        
        while (!min_heap.empty()) {
            // All meetings at this time instant
            vector<Meeting> meetings;            
            int time = min_heap.top().time;
            unordered_map<int, unordered_set<int>> connected;
            unordered_set<int> visited;
                        
            while (!min_heap.empty() && min_heap.top().time == time) {
                const Meeting& m = min_heap.top();
                meetings.push_back(m);
                connected[m.x].insert(m.y);
                connected[m.y].insert(m.x);
                if (uf.is_person_infected(m.x)) {visited.insert(m.x);}
                if (uf.is_person_infected(m.y)) {visited.insert(m.y);}
                min_heap.pop();                
            }
            
            queue<int> infect;
            for (int i : visited) {infect.push(i);}
            
            
            while (!infect.empty()) {
                int person = infect.front(); infect.pop();
                for (int neigh : connected[person]) {
                    if (visited.find(neigh) != visited.end()) continue;
                    visited.insert(neigh);
                    infect.push(neigh);
                    uf.uf_union(uf.uf_find(neigh), uf.uf_find(person));
                }
            }            
        }
        
        vector<int> ans = uf.getInfected();
        return ans;
    }
};

















