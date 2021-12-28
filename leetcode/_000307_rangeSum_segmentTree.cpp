class NumArray {
    int N;
    vector<int> seg_tree;
    
    // node is the node index in the tree
    // lo/hi are bounds of the subarray
    // index, val corresponds to the array element to update
    int updateInternal(int node, int lo, int hi, int index, int val) {
        if (lo == hi) {
            int prev_val = seg_tree[node];
            seg_tree[node] = val;
            return val-prev_val;  // returns delta, so upstream can modify it
        }
        
        int mid = (lo+hi)/2;
        int delta=0;
        if (index <= mid) {
            delta = updateInternal(2*node+1, lo,    mid, index, val);            
        } else {
            delta = updateInternal(2*node+2, mid+1, hi,  index, val);            
        }
        seg_tree[node] += delta;
        return delta;
    }
    
    // lo/hi is what the current node covers
    // query_lo/query_hi is the query range
    int sumInternal(int node, int lo, int hi, int query_lo, int query_hi) {
        if (lo > query_hi) return 0;
        if (hi < query_lo) return 0;
        if (query_lo <= lo && query_hi >= hi) {
            // query range encompasses me entirely
            return seg_tree[node];
        }
        int mid=(lo+hi)/2;
        int lhs = sumInternal(2*node+1, lo, mid, query_lo, query_hi);
        int rhs = sumInternal(2*node+2, mid+1, hi, query_lo, query_hi);
        return lhs+rhs;
    }
    
public:
    NumArray(vector<int>& nums) {
        N = nums.size();
        seg_tree = vector<int>(4*N, 0);        
        
        for (int i=0; i<nums.size(); i++) {
            update(i, nums[i]);
        }
    }
    
    // O(log n) time, O(n) space.
    void update(int index, int val) {
        if (index >= N) return;
        updateInternal(0, 0, N-1, index, val);
    }
    
    // O(log n) time, O(n) space.
    int sumRange(int left, int right) {
        return sumInternal(0, 0, N-1, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
