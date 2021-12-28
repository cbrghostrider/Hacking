class SnapshotArray {
    struct Info {
        int val=0;  // the current value
        unordered_map<int, int> snaps;
    };
    int next_id=0;
    vector<Info> data;
public:
    SnapshotArray(int length) {
        data = vector<Info>(length, Info());
    }
    
    // O(1) set operation.
    void set(int index, int val) {
        if (index >= data.size()) return;  // invalid index
        data[index].val = val;
    }
    
    // O(n) snap operation.
    // Snap is too expensive, leading to TLE
    int snap() {
        for (Info& info : data) {
            info.snaps[next_id] = info.val;
        }
        next_id++;
        return next_id-1;
    }
    
    // O(1) get operation.
    int get(int index, int snap_id) {
        if (snap_id >= next_id) return -1;    // no valid snapshot
        if (index >= data.size()) return -1;  // invalid index
        return data[index].snaps[snap_id];
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
