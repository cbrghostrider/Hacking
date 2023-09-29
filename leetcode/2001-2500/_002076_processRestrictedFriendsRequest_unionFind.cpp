class Solution {
    unordered_map<int, set<int>> haters;
    
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
        if (sizes[leader1] >= sizes[leader2]) {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2]; 
            for (int h : haters[leader2]) {
                haters[leader1].insert(h);
            }
        } else {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];
            for (int h : haters[leader1]) {
                haters[leader2].insert(h);
            }
        }
    }
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        for (const vector<int>& rest : restrictions) {
            haters[rest[0]].insert(rest[1]);
            haters[rest[1]].insert(rest[0]);
        }
        for (int i=0; i<n; i++) {
            leaders.push_back(i);
            sizes.push_back(1);
        }
        vector<bool> ans;
        for (const vector<int>& fr : requests) {
            int p1 = fr[0];
            int p2 = fr[1];
            int l1 = uf_find(p1);
            int l2 = uf_find(p2);
            if (l1 == l2) {
                ans.push_back(true);
                continue;
            }
            
            bool val = true;
            for (int check : haters[l1]) {
                int lc = uf_find(check);
                if (lc == l2 || p2 == check) {
                    val = false;
                    break;
                }
            }
            if (val) {
                for (int check : haters[l2]) {
                    int lc = uf_find(check);
                    if (lc == l1 || p1 == check) {
                        val = false;
                        break;
                    }
                }                
            }
            ans.push_back(val);
            if (val) {uf_union(l1, l2);}
        }
        
        return ans;
    }
};
