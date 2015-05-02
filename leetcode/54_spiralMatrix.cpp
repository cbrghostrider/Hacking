class Solution {
public:
    bool doneRec(int rs, int re, int cs, int ce) {
        return (rs > re || cs > ce);
    }
    
    //strips top row of matrix, from left to right
    vector<int> spiralT(const vector<vector<int> >& ip, int rs, int re, int cs, int ce) {
        vector<int> retval;
        if (doneRec(rs, re, cs, ce)) return retval;
        
        for (int i=cs; i<=ce; i++) retval.push_back(ip[rs][i]);
        
        vector<int> rest = spiralR(ip, rs+1, re, cs, ce);
        if (rest.size() > 0) retval.insert(retval.end(), rest.begin(), rest.end());

        return retval;
    }
        
    //strips right row of matrix, from top to bottom
    vector<int> spiralR(const vector<vector<int> >& ip, int rs, int re, int cs, int ce) {
        vector<int> retval;
        if (doneRec(rs, re, cs, ce)) return retval;
        
        for (int i=rs; i<=re; i++) retval.push_back(ip[i][ce]);
        
        vector<int> rest = spiralB(ip, rs, re, cs, ce-1);
        if (rest.size() > 0) retval.insert(retval.end(), rest.begin(), rest.end());

        return retval;
    }
    
    //strips bottom row of matrix, from right to left
    vector<int> spiralB(const vector<vector<int> >& ip, int rs, int re, int cs, int ce) {
        vector<int> retval;
        if (doneRec(rs, re, cs, ce)) return retval;
        
        for (int i=ce; i>=cs; i--) retval.push_back(ip[re][i]);
        
        vector<int> rest = spiralL(ip, rs, re-1, cs, ce);
        if (rest.size() > 0) retval.insert(retval.end(), rest.begin(), rest.end());

        return retval;
    }
    
    //strips left row of matrix, from bottom to top
    vector<int> spiralL(const vector<vector<int> >& ip, int rs, int re, int cs, int ce) {
        vector<int> retval;
        if (doneRec(rs, re, cs, ce)) return retval;
        
        for (int i=re; i>=rs; i--) retval.push_back(ip[i][cs]);
        
        vector<int> rest = spiralT(ip, rs, re, cs+1, ce);
        if (rest.size() > 0) retval.insert(retval.end(), rest.begin(), rest.end());

        return retval;
    }
    
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (matrix.empty() || matrix[0].empty()) {
            vector<int> retval;
            return retval;
        }
        
        int n = matrix[0].size();
        if (n == 1) {
            return spiralR(matrix, 0, m-1, 0, n-1);
        }
        return spiralT(matrix, 0, m-1, 0, n-1);
    }
};
