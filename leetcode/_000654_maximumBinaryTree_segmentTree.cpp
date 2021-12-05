/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    vector<pair<int, int>> seg_tree;  // stores (max_val, index)
    
    // lhs, rhs are (max_val, index) pairs.
    pair<int, int> merge(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        if (lhs.second == -1) return rhs;
        if (rhs.second == -1) return lhs;
        if (lhs.first < rhs.first) return rhs;
        return lhs;
    }
    
    void buildSegmentTree(const vector<int>& nums, int my_index, int lo, int hi) {
        if (my_index == 0) {seg_tree = vector<pair<int, int>>(4*nums.size(), {-1, -1});}
        if (lo == hi) {
            seg_tree[my_index] = make_pair(nums[lo], lo);
            return;
        }
        
        int mid = (lo+hi)/2;
        buildSegmentTree(nums, my_index*2+1, lo, mid);
        buildSegmentTree(nums, my_index*2+2, mid+1, hi);
        seg_tree[my_index] = merge(seg_tree[my_index*2+1], seg_tree[my_index*2+2]);
    }
    
    // returns (max_val, index) of maximum value in range [i, j]
    // my_index is current index, [lo, hi] is the segment for current index
    // [i, j] is the query we are interested in
    // we recurse, checking for overlap
    pair<int,int> querySegTree(int my_index, int lo, int hi, int i, int j) {
        if (lo > j || hi < i) {return {-1, -1};}  // no overlap
        if (lo >= i && hi <= j) {  // full overlap, no need to recurse
            return seg_tree[my_index];
        }
        int mid = (lo+hi)/2;
        pair<int, int> cand1 = querySegTree(my_index*2+1, lo, mid, i, j);
        pair<int, int> cand2 = querySegTree(my_index*2+2, mid+1, hi, i, j);
        pair<int, int> ans = merge(cand1, cand2);
        return ans;
    }
    
    int maxIndexLinearScan(const vector<int>& nums, int begin, int end) {
        int index = -1, max = std::numeric_limits<int>::min();
        for (int i=begin; i<=end; i++) {
            if (nums[i] > max) {
                max = nums[i];
                index = i;
            }
        }
        return index;
    }
    
    // constructs a maximum binary tree from [begin, end] indices of nums.
    TreeNode * getBinaryTree(const vector<int>& nums, int begin, int end) {
        if (begin == end) {return new TreeNode(nums[begin]);}
        
        // Using linear scan is O(n) time.
        // int index = maxIndexLinearScan(nums, begin, end);
        
        // Using segment tree is O(logn) time.
        int index = querySegTree(0, 0, nums.size()-1, begin, end).second;
        
        TreeNode *me = new TreeNode(nums[index]);
        me->left = index == begin ? nullptr : getBinaryTree(nums, begin, index-1);
        me->right = index == end ? nullptr : getBinaryTree(nums, index+1, end);
        return me;
    }
public:
    // O(n) space for the recursion.
    // O(n log n) time if using segment tree to find max in range.
    // O(n^2) time if using linear scan to find max in range.
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        buildSegmentTree(nums, 0, 0, nums.size()-1);
        return getBinaryTree(nums, 0, nums.size()-1);
    }
};
