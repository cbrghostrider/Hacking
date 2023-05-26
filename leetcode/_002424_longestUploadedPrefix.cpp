class LUPrefix {
    int N;
    vector<int> leaders;
    vector<int> sizes;    
    
    // Return the index of the leader.
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
    LUPrefix(int n) {
        N = n;
        leaders = vector<int>(n, 0);
        sizes = vector<int>(n, 0);  
        for (int i=0; i<n; i++) {
            leaders[i] = i;
        }      
    }
    
    void upload(int video) {
        int ind=video-1;
        sizes[ind] = 1;
        if (ind != 0 && sizes[ind-1] != 0) {
            int ld_left = uf_find(ind-1);            
            uf_union(ind, ld_left);
        }
        if (ind != N-1 && sizes[ind+1] != 0) {
            int ld_me = uf_find(ind);
            int ld_right = uf_find(ind+1);            
            uf_union(ld_me, ld_right);
        }
    }
    
    int longest() {
        if (sizes[0] == 0) return 0;
        int ld = uf_find(0);
        return sizes[ld];
    }
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */
