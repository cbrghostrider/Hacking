//
// There are m rows and n cols.
// A number can be chosen from any row in n `choose` m ways. i.e. n ways
// Total choices to get an array of size m: n x n x n x n x ..... x n (m-times) = n `pow` m
//
// It is easy to say what the lowest sum array is. Just the 0th index of each row is chosen.
// It is also easy to say what the next one is. Take the delta between 0th and 1st index for all
// rows. The lowest delta is the row chosen to advance its pointer.
//
// In general maintain m pointers.
// However, once we are in some intermediate state, with pointers at various stages of 
// advancement, it becomes much more tricky.
// Now if you advance a single pointer, say for row 1, you need to factor in the various 
// "intermediate" arrays generated. For example...
// 
// Consider 4 rows, with pointers at 4, 2, 3, 3
// Say you advance the 1-st row (0 indexed) pointer from 2->3
// Now you have all combos of array-sums for arrays with pointers:
// Row 0: Ptr from 0 to 4
// Row 1: Pointer at 3 (this was advanced)
// Row 2: Ptr from 0 to 3
// Row 3: Ptr from 0 to 3
// All these subarray sums need to be generated, and added to the heap.
//
class Solution {
    struct DeltaInfo {
        int delta=0;  // the delta between cur_ptr elem at this row, and cur_ptr+1 element at this row
        int row=0;
        int cur_ptr=0;
        int sum=0;    // the sum for cur_ptr; used along with delta to maintain heap property
    };
    struct SASumInfo {
        int sum=0;    // the subarray sum for this repr
        string repr;  // the repr, which is a string concat of all the row ptr indices for this sum
    };
    
    vector<vector<int>> matrix;    
    int R, C;
    
    vector<int> global_ptrs;  // says where the current pointers are for every row
    unordered_map<string, int> sa_sums;   // cached subarray sums for "repr" to quickly 
                                          // compute subarray sums from the past
    
    function<bool(const DeltaInfo&, const DeltaInfo&)> deltacomp = 
        [](const DeltaInfo& lhs, const DeltaInfo& rhs) -> bool {
        int lhs_sum = lhs.sum + lhs.delta;
        int rhs_sum = rhs.sum + rhs.delta;
        if (lhs_sum != rhs_sum) return lhs_sum > rhs_sum;
        return lhs.row > rhs.row;
    };
    
    function<bool(const SASumInfo&, const SASumInfo&)> sasumcomp = 
        [](const SASumInfo& lhs, const SASumInfo& rhs) -> bool {
        if (lhs.sum != rhs.sum) return lhs.sum > rhs.sum;
        return false;
    };
    
    // This heap helps us decide *which row pointer* to advance next.
    using DeltaHeap=priority_queue<DeltaInfo, vector<DeltaInfo>, decltype(deltacomp)>;
    DeltaHeap delta_heap;
    
    // This heap helps us decide *which subarray sum* is next lowest sum.
    using SASumHeap=priority_queue<SASumInfo, vector<SASumInfo>, decltype(sasumcomp)>;
    SASumHeap sasum_heap;
    
    // Given the state of pointers, returns the repr.
    string getRepr(const vector<int>& ptrs) {
        string ret;
        for (int n : ptrs) {
            ret += to_string(n) + "-";
        }
        return ret;
    }
    
    vector<vector<int>> getAdvances(vector<vector<int>>& prev, int row, int skip_row) {
        vector<vector<int>> ans;
        if (row == skip_row) {
            for (vector<int>& p : prev) {
                p.push_back(global_ptrs[skip_row]);  // use old coord
                ans.push_back(p);
                p.pop_back();
            }
            return ans;
        }
        
        for (vector<int>& p : prev) {  // by value on purpose
            for (int i=0; i<=global_ptrs[row]; i++) {
                p.push_back(i);
                ans.push_back(p);
                p.pop_back();
            }
        }
        return ans;
    }
    
    // Given the current global pointers, advance the pointer for the specified row.
    // Note that this also generates the intermediate reprs, and sums, and adds them
    // to the sasum_heap.
    // At the end, if possible, it also adds another entry to the delta_heap.
    void advance(int row) {
        if (global_ptrs[row] >= C-1) return;  // nothing to advance; should not happen!
        
        vector<vector<int>> sa_indices;
        sa_indices.push_back({});
        
        for (int i=0; i<global_ptrs.size(); i++) {
            sa_indices = getAdvances(sa_indices, i, row);
        }
        
        for (vector<int>& sai : sa_indices) {
            string repr = getRepr(sai);
            int sum = sa_sums[repr];
            
            // We will remove the element for global_ptr[row] and add the next one in that row
            sum -= matrix[row][global_ptrs[row]];
            sum += matrix[row][global_ptrs[row]+1];
            
            sai[row]++;
            string next_repr = getRepr(sai);
            sa_sums[next_repr] = sum;
            
            sasum_heap.push({sum, next_repr});
        }
        
        // Advance it!
        global_ptrs[row]++;
        
        if (global_ptrs[row] < C-1) {
            int delta = matrix[row][global_ptrs[row]+1] - matrix[row][global_ptrs[row]];
            vector<int> min_ptrs(global_ptrs.size(), 0);
            min_ptrs[row] = global_ptrs[row];
            string repr = getRepr(min_ptrs);
            int sum = sa_sums[repr];
            delta_heap.push({delta, row, global_ptrs[row], sum});
        }
    }
public:
    //
    // Solution is functionally correct, but runs into TLE.
    // O(R^C * log R^C) time...
    //
    int kthSmallest(vector<vector<int>>& mat, int k) {
        matrix = mat;
        R=matrix.size();
        C=matrix[0].size();
        delta_heap = DeltaHeap(deltacomp);
        sasum_heap = SASumHeap(sasumcomp);
        
        int sum=0;
        for (int r=0; r<R; r++) {
            sum += matrix[r][0];
            global_ptrs.push_back(0);
        }
        for (int r=0; r<R && C>1; r++) {
            int delta = matrix[r][1] - matrix[r][0];
            delta_heap.push({delta, r, 0, sum});
        }
        string repr=getRepr(global_ptrs);
        sa_sums[repr] = sum;
        sasum_heap.push({sum, repr});
        auto& ssh=sasum_heap; auto& dh=delta_heap;
        while (1) {
            // candidate 1; we advanced the "best" pointer
            int c1 = delta_heap.empty() ? std::numeric_limits<int>::max() 
                                        : delta_heap.top().sum + delta_heap.top().delta; 
            
            // candidate 2 from the heap of sa_sums so far
            int c2 = sasum_heap.empty() ? std::numeric_limits<int>::max() 
                                        : sasum_heap.top().sum; 
            
            if (c1 <= c2) {
                auto elem = delta_heap.top();
                delta_heap.pop();
                advance(elem.row);
                continue;
            }
            
            int next_sum = sasum_heap.top().sum;
            sasum_heap.pop();
            
            if (k == 1) {return next_sum;}
            k--;
        }
        
        return -1;  // should not get here, unless k was too large (not possible per problem limits)
    }
};
