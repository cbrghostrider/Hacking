class Solution {
    int N;
    vector<int> max_path_at_node;

    int compute_max_path_at_node(int node, const vector<int>& cost) {
        if (node >= N) return 0;
        int left = 2*node + 1;
        int right = 2*node + 2;
        int lhs = compute_max_path_at_node(left, cost); 
        int rhs = compute_max_path_at_node(right, cost);
        max_path_at_node[node] = std::max(lhs + cost[node], rhs + cost[node]);       
        return max_path_at_node[node];
    }

    // sum_so_far is sum from above accounted for so far
    // returns how many increments needed in this sub-tree
    int push_down(int node, const int max_path, int sum_so_far, const vector<int>& cost) {
        if (node >= N) return 0;
        int left = 2*node + 1;
        int right = 2*node + 2;  

        int max_child_path = (left >=N || right >= N) ? 0 : std::max(max_path_at_node[left], max_path_at_node[right]);
        int my_inc = max_path - sum_so_far - max_child_path - cost[node];
        sum_so_far += my_inc + cost[node];
        
        int lhs = push_down(left, max_path, sum_so_far, cost);        
        int rhs = push_down(right, max_path, sum_so_far, cost);        
        return (my_inc + lhs + rhs);
    }
public:
    int minIncrements(int n, vector<int>& cost) {
        N = n;
        max_path_at_node = vector<int>(n, 0);
        compute_max_path_at_node(0, cost);
        int max_path = max_path_at_node[0];
        int incs = push_down(0, max_path, 0, cost);
        return incs;
    }
};
