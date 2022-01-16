/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
    int N;
    vector<vector<int>> num_ones;
    
    void init(const vector<vector<int>>& grid) {
        num_ones = vector<vector<int>>(N, vector<int>(N, 0));
        int sum=0;
        for (int c=0; c<N; c++) {
            sum += grid[0][c];
            num_ones[0][c] = sum;
        }
        sum=0;
        for (int r=0; r<N; r++) {
            sum += grid[r][0];
            num_ones[r][0] = sum;
        }        
        for (int r=1; r<N; r++) {
            for (int c=1; c<N; c++) {
                num_ones[r][c] = grid[r][c] + num_ones[r-1][c] + num_ones[r][c-1] - num_ones[r-1][c-1];
            }
        }
    }
    
    // returns number of ones in sub-square with top-left, and bottom-right crds
    int queryOnes(int r_tl, int c_tl, int r_br, int c_br) {
        if (r_tl < 0  || c_tl < 0  || r_br < 0  || c_br < 0 || 
            r_tl >= N || c_tl >= N || r_br >= N || c_br >= N) {
            return 0;  // invalid; should not happen
        }
        
        int QTL=0, QTR=0, QBL=0;
        if (r_tl-1 >= 0 && c_tl-1 >= 0) {
            QTL=num_ones[r_tl-1][c_tl-1];
        }
        if (r_tl-1 >= 0) {
            QTR=num_ones[r_tl-1][c_br];
        }
        if (c_tl-1 >= 0) {
            QBL=num_ones[r_br][c_tl-1];
        }
        int ret = num_ones[r_br][c_br] - QTR - QBL + QTL;
        return ret;
    }
    
    // returns the size of the sub-square
    int querySize(int r_tl, int c_tl, int r_br, int c_br) {
        if (r_tl < 0  || c_tl < 0  || r_br < 0  || c_br < 0 || 
            r_tl >= N || c_tl >= N || r_br >= N || c_br >= N) {
            return 0;  // invalid; should not happen
        }
        int len = r_br-r_tl+1;
        int wid = c_br-c_tl+1;
        return (len * wid);
    }
    
    Node* getQTree(int r_tl, int c_tl, int r_br, int c_br) {
        int ones = queryOnes(r_tl, c_tl, r_br, c_br);
        int size = querySize(r_tl, c_tl, r_br, c_br);
        
        if (ones == 0 || ones == size) {
            // also covers recursion base case of size = 1
            Node* node = new Node(ones != 0, /*is_leaf=*/true);
            return node;
        } 
        
        int mid_col    = c_tl + (c_br-c_tl+1)/2;
        int mid_col_m1 = mid_col - 1;
        int mid_row    = r_tl + (r_br-r_tl+1)/2;
        int mid_row_m1 = mid_row - 1;
        
        Node* node = new Node();
        node->isLeaf = node->val = false;
        
        node->topLeft     = getQTree(r_tl,    c_tl,    mid_row_m1, mid_col_m1);
        node->topRight    = getQTree(r_tl,    mid_col, mid_row_m1, c_br);
        node->bottomLeft  = getQTree(mid_row, c_tl,    r_br,       mid_col_m1);
        node->bottomRight = getQTree(mid_row, mid_col, r_br,       c_br);
        
        return node;
    }
    
public:
    // O(N^2) time, O(N^2) space.
    Node* construct(vector<vector<int>>& grid) {
        N=grid.size();                
        init(grid);
        Node* ret = getQTree(0, 0, N-1, N-1);
        return ret;
    }
};
