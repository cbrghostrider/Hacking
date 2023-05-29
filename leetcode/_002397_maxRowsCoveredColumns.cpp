class Solution {
    int R, C;
    unordered_set<int> picked;

    // Evaluate looks at picked, and decides what rows are covered.
    int evaluate(const vector<vector<int>>& matrix) {
        int count=0;
        for (int r=0; r<R; r++) {            
            bool possible = true;
            for (int c=0; c<C; c++) {
                if (matrix[r][c] == 1 && picked.find(c) == picked.end()) {
                    possible = false;
                    break;
                }
            }
            if (possible) {count++;}
        }
        return count;
    }

    // We will pick/drop index with backtracking, and recurse.
    int explore(const vector<vector<int>>& matrix, int index, int remaining) {
        if (index == C || remaining == 0) {
            return evaluate(matrix);
        }        
        if (C - index <= remaining) {
            // All remaining indices can be picked.
            for (int c=index; c<C; c++) {
                picked.insert(c);                
            }
            int val = evaluate(matrix);
            // Backtrack.
            for (int c=index; c<C; c++) {
                picked.erase(c);                
            }
            return val;
        }

        // pick index
        picked.insert(index);
        int val1 = explore(matrix, index+1, remaining-1);
        
        // drop index
        picked.erase(index);
        int val2 = explore(matrix, index+1, remaining);
        return std::max(val1, val2);
    }

public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        R=matrix.size();
        C=matrix[0].size();

        int ans = explore(matrix, 0, numSelect);
        return ans;
    }
};
