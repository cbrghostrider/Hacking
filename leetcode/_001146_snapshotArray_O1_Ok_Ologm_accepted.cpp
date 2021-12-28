class SnapshotArray {
    struct Info {
        int val=0;  // the current value
        
        // index i (v, x) means 
        // (assuming index i-1 was (u, y))
        // from snap_id u+1 to snap id v, the value of this cell was x
        // we can binary search on v to find the snap_id in log time.
        vector<pair<int, int>> snaps;
    };
    
    // indices updated since last snap
    unordered_set<int> updates;
    
    int next_id=0;
    vector<Info> data;
    
    // Binary searches data[index]'s info, and returns the value of 
    // data corresponding to snap_id
    int search(int index, int snap_id, int lo, int hi) {
        Info& di = data[index];
        if (data[index].snaps.size() == 0) {return data[index].val;}
        if (lo == hi) {
            return data[index].snaps[lo].second;
        }
        if (lo+1 == hi) {
            if (data[index].snaps[lo].first >= snap_id) {
                return data[index].snaps[lo].second;
            } 
            return data[index].snaps[hi].second;
        }
        int mid = (lo+hi)/2;
        if (data[index].snaps[mid].first == snap_id) {
            return data[index].snaps[mid].second;
        }
        if (data[index].snaps[mid].first > snap_id) {
            if (data[index].snaps[mid-1].first < snap_id) {
                return data[index].snaps[mid].second;
            }
            return search(index, snap_id, lo, mid);
        }
        if (data[index].snaps[mid+1].first >= snap_id) {
            return data[index].snaps[mid+1].second;
        }
        return search(index, snap_id, mid+1, hi);
    }
public:
    // O(n) time constructor.
    SnapshotArray(int length) {
        data = vector<Info>(length, Info());
    }
    
    // O(1) time set.
    void set(int index, int val) {
        if (index >= data.size()) return;  // invalid index
        if (data[index].snaps.empty() && next_id != 0)  {
            data[index].snaps.push_back({next_id-1, data[index].val});
        } else if (!data[index].snaps.empty() && 
                   data[index].snaps.back().first < next_id-1) {
            data[index].snaps.push_back({next_id-1, data[index].val});
        }
        data[index].val = val;
        updates.insert(index);
    }
    
    // O(k) time, where k = # of unique index updates since last snap.
    int snap() {
        for (int index : updates) {
            data[index].snaps.push_back({next_id, data[index].val});
        }
        updates.clear();
        next_id++;
        return next_id-1;
    }
    
    // O(log m) time, where m=# of snaps.
    int get(int index, int snap_id) {
        if (snap_id >= next_id) return -1;    // no valid snapshot
        if (index >= data.size()) return -1;  // invalid index
        int val = search(index, snap_id, 0, data[index].snaps.size()-1);
        return val;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
