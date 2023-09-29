class Solution {
    int m=0;  // num rows
    int n=0;  // num cols
public:
    int N(const vector<vector<int>>& img, int r, int c) {
        return (r == 0 ? 0 : img[r-1][c]);
    }
    int S(const vector<vector<int>>& img, int r, int c) {
        return (r == m-1 ? 0 : img[r+1][c]);
    }
    int E(const vector<vector<int>>& img, int r, int c) {
        return (c == n-1 ? 0 : img[r][c+1]);
    }
    int W(const vector<vector<int>>& img, int r, int c) {
        return (c == 0 ? 0 : img[r][c-1]);
    }
    int NE(const vector<vector<int>>& img, int r, int c) {
        return (r == 0 || c == n-1 ? 0 : img[r-1][c+1]);
    }
    int NW(const vector<vector<int>>& img, int r, int c) {
        return (r == 0 || c == 0 ? 0 : img[r-1][c-1]);
    }
    int SE(const vector<vector<int>>& img, int r, int c) {
        return (r == m-1 || c == n-1 ? 0 : img[r+1][c+1]);
    }
    int SW(const vector<vector<int>>& img, int r, int c) {
        return (r == m-1 || c == 0 ? 0 : img[r+1][c-1]);
    }
    int getSum(const vector<vector<int>>& img, int r, int c) {
        return (img[r][c] + 
                N(img, r, c) + S(img, r, c) + E(img, r, c) + W(img, r, c) +
                NE(img, r, c) + NW(img, r, c) + SE(img, r, c) + SW(img, r, c));
    }
    
    // Special case to smooth a 1-row or 1-col image.
    vector<vector<int>> smooth1D(const vector<vector<int>>& img) {
        vector<vector<int>> ans = img;
        if (m == 1) {
            for (int ni=0; ni<n; ni++) {
                int d = (ni == 0 || ni == n-1 ? 2 : 3);
                int sum = getSum(img, 0, ni);
                ans[0][ni] = sum / d;
            }
        } else {  // n == 1
            for (int mi=0; mi<m; mi++) {
                int d = (mi == 0 || mi == m-1 ? 2 : 3);
                int sum = getSum(img, mi, 0);
                ans[mi][0] = sum / d;
            }
        }
        return ans;
    }
    
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        m = img.size();
        n = img[0].size();
        
        if (m == 1 && n == 1) return img;
        if (m == 1 || n == 1) return smooth1D(img);
        
        vector<vector<int>> ans = img;
        for (int mi=0; mi<m; mi++) {
            for (int ni = 0; ni < n; ni++) {
                int sum = getSum(img, mi, ni);
                int d = 9;
                if ((mi == 0 || mi == m-1) && (ni == 0 || ni == n-1)){
                    d = 4;
                } else if (mi == 0 || mi == m-1 || ni == 0 || ni == n-1) {
                    d = 6;
                }
                ans[mi][ni] = sum/d;
            }
        }
        return ans;
    }
};
