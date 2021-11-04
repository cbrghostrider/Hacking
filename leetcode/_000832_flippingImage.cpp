class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
        const int N = image[0].size();
        bool invert_middle = ((N % 2) == 1);
        
        vector<vector<int>> image_ans = image;
        for (vector<int>& row : image_ans) {
            for (int i=0; i<N/2; i++) {
                int temp = row[i];
                row[i] = (row[N-1-i] ? 0 : 1);
                row[N-1-i] = (temp ? 0 : 1);
            }
            if (invert_middle) {
                row[N/2] = (row[N/2] ? 0 : 1);
            }
        }
        return image_ans;
    }
};
