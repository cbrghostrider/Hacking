class Solution {
    vector<vector<char>> transposeMirror(const vector<vector<char>>& box) {
        vector<vector<char>> ret(box[0].size(), vector<char>(box.size(), ' '));
        for (int r=0; r<box.size(); r++) {
            for (int c=0; c<box[0].size(); c++) {
                ret[c][box.size() - 1 - r] = box[r][c];
            }
        }
        return ret;
    }
    
    void collapse(vector<vector<char>>& box) {
        for (int c=0; c<box[0].size(); c++) {
            int put_ptr=box.size()-1;
            for (int check=box.size()-1; check>=0; ) {
                if (box[check][c] == '*') {
                    put_ptr = check = check-1;                    
                } else if (box[check][c] == '.') {
                    check--;                    
                } else {  // stone
                    std::swap(box[put_ptr][c], box[check][c]);
                    put_ptr--;
                    check--;
                }
            }
        }
    }
    
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        vector<vector<char>> tm = transposeMirror(box);
        collapse(tm);
        return tm;
    }
};
