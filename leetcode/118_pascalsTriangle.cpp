class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> pascal;
        if (numRows <= 0) return pascal;
        
        pascal.push_back(vector<int>(1, 1));
        if (numRows == 1) return pascal;
        
        pascal.push_back(vector<int>(2, 1));
        for (int i=2; i<numRows; i++) {
            pascal.push_back(vector<int>());
            pascal[i].push_back(1);
            for (int p=1; p<pascal[i-1].size(); p++) {
                pascal[i].push_back(pascal[i-1][p-1] + pascal[i-1][p]);
            }
            pascal[i].push_back(1);
        }
        return pascal;
    }
};
