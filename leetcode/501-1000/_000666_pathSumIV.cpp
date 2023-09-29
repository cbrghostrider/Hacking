class Solution {
    const int L=4;  // the max number of levels
    const int N=8;  // max nodes in any level
    int max_level=-1;
    const int ROOT_LEVEL=1;
    const int ROOT_NODE=1;
    
    // A poor man's representation of a tree.
    // +1 makes it 1-indexed for ease.
    // A value of -1 means that node does not exist (akin to nullptr)
    // At any level l, for node n, children are (posibly) at level l+1 
    // with children nodes numbered 2(n-1)+1 and 2(n-1)+2
    vector<vector<int>> tree;
    
    vector<pair<int, int>> noteAllLeaves() {
        vector<pair<int, int>> ans;
        for (int l=1; l<=max_level; l++) {
            for (int n=1; n<=N; n++) {
                if (tree[l][n] == -1) continue;
                int c1 = 2*(n-1)+1;
                int c2 = 2*(n-1)+2;
                if (l == max_level || (tree[l+1][c1] == -1 && tree[l+1][c2] == -1)) {
                    ans.push_back({l, n});
                }
            }
        }
        return ans;
    }
    
    // starting from element at stated level and node, calculate the path sum moving up to root
    int pathSum(int leaf_level, int leaf_node) {
        int sum=0;
        while (!(leaf_level == 1 && leaf_node == 1)) {
            sum += tree[leaf_level][leaf_node];
            leaf_level -= 1;
            leaf_node = (leaf_node - 1)/2 + 1;
        } 
        return sum + tree[1][1];
    }

public:
    int pathSum(vector<int>& nums) {    
        tree = vector<vector<int>>(L+1, vector<int>(N+1, -1));
        // let's construct the tree representation
        for (int n : nums) {
            int level = n/100;
            int node = (n - (n/100)*100)/10;
            int val = n%10;
            tree[level][node] = val;
            if (level > max_level) {max_level = level;}
        }
        
        vector<pair<int, int>> leaves = noteAllLeaves();
        int total=0;
        for (pair<int, int> ln : leaves) {
            total += pathSum(ln.first, ln.second);
        }
        return total;
    }
};
