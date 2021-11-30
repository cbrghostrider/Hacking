class Solution {
public:
    // O(M*K*N) time, O(M*N) space.
    // Brute force
    vector<vector<int>> multiplyBF(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        const int M=mat1.size();
        const int K=mat1[0].size();
        const int N=mat2[0].size();
        
        vector<vector<int>> ans(M, vector<int>(N, 0));
        for (int m=0; m<M; m++) {
            for (int n=0; n<N; n++) {
                int elem=0;
                for (int k=0; k<K; k++) {
                    elem += mat1[m][k] * mat2[k][n];
                }
                ans[m][n] = elem;
            }
        }
        return ans;
    }

  // The solution below uses custom data structure to store a sparse matrix more efficiently for mat-mult.
  // It ran in 0 ms lol. Correct answer.
  class Sparse {
    public:
      Sparse(const vector<vector<int>>& mat) : data(mat), R(mat.size()), C(mat[0].size()) {
          for (int r=0; r<R; r++) {
              bool row_exists = false;
              int row_starts = row_elem_info.size();
              for (int c=0; c<C; c++) {
                  if (mat[r][c] == 0) continue;
                  row_exists = true;
                  row_elem_info.push_back(make_pair(r, c));
              }
              row_info.push_back(make_pair(row_starts, row_exists));
          }
          
          for (int c=0; c<C; c++) {
              bool col_exists = false;
              int col_starts = col_elem_info.size();
              for (int r=0; r<R; r++) {
                  if (mat[r][c] == 0) continue;
                  col_exists = true;
                  col_elem_info.push_back(make_pair(r, c));
              }
              col_info.push_back(make_pair(col_starts, col_exists));
          }
      }
      
      void Multiply(Sparse& rhs, vector<vector<int>>& result) {
          if (C != rhs.R) return;

          int lhs_ci_ptr=-1, rhs_ri_ptr=-1;
          for (int r=0; r<R; r++) {
              for (int c=0; c<rhs.C; c++) {
                  lhs_ci_ptr++; rhs_ri_ptr++;
                  if (row_info[r].second == false || rhs.col_info[c].second == false) {continue;}
                  
                  int lhs_ptr = row_info[r].first;
                  int rhs_ptr = rhs.col_info[c].first;
                  
                  int elem = 0;
                  while (lhs_ptr<row_elem_info.size() && row_elem_info[lhs_ptr].first == r &&
                        rhs_ptr<rhs.col_elem_info.size() && rhs.col_elem_info[rhs_ptr].second == c) {
                      int k_index_lhs = row_elem_info[lhs_ptr].second;    // c in first matrix
                      int k_index_rhs = rhs.col_elem_info[rhs_ptr].first; // r in second matrix
                      if (k_index_lhs == k_index_rhs) {  // k matches: (r, k) * (k, c) for the two matrices
                          elem += data[r][k_index_lhs] * rhs.data[k_index_rhs][c];
                          lhs_ptr++; rhs_ptr++;
                      } else if (k_index_lhs < k_index_rhs) {
                          lhs_ptr++;
                      } else {
                          rhs_ptr++;
                      }
                  }
                  result[r][c] = elem;
              }
          }
      }
      
    private:
      const vector<vector<int>>& data;
      const int R;
      const int C;
      
      // metadata
      // stores (row,col) for every non-zero element in matrix, "in order" r:0->N, c:0->M
      vector<std::pair<int, int>> row_elem_info;
      // similarly for col_elem_info; "in order" c:0->M, r:0->N
      vector<std::pair<int, int>> col_elem_info;
      
      // Index i stores whether row i exists in data as follows:
      // bool is true if at least 1 non-zero element in row i
      // int is index of first non-zero element in row i "as stored in row_elem_info"
      vector<std::pair<int, bool>> row_info;      
      // similarly for col_info
      vector<std::pair<int, bool>> col_info;
  };
    
    
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        Sparse s1(mat1), s2(mat2);
        vector<vector<int>> result(mat1.size(), vector<int>(mat2[0].size(), 0));
        s1.Multiply(s2, result);
        return result;
    }
};
