class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return;
        for (int layer=0; layer<matrix.size()/2; layer++) {
            int ctrlast = matrix.size()-1-layer;
            int rt = layer, rb = ctrlast; //row top and bottom
            int cl = layer, cr = ctrlast; //col left and right
            for (int ctr=layer; ctr<ctrlast; ctr++) {
                int temp = matrix[rt][ctr];
                matrix[rt][ctr] = matrix[matrix.size()-1-ctr][cl];
                matrix[matrix.size()-1-ctr][cl] = matrix[rb][matrix.size()-1-ctr];
                matrix[rb][matrix.size()-1-ctr] = matrix[ctr][cr];
                matrix[ctr][cr] = temp;
            }
        }
    }
};
