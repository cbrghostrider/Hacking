class Solution {
    struct Info {
        bool single = false;
        std::pair<int, int> rc;
        Info() {rc = make_pair(-1, -1);}
    };
    int R = 0;
    int C = 0;
public:
    // O(R*C) time, O(R) space.
    int numSpecial(vector<vector<int>>& mat) {
        R = mat.size();
        C = mat[0].size();
        vector<Info> row_info(R, Info());
        
        for (int ri=0; ri<R; ri++) {
            Info& info = row_info[ri];
            for (int ci=0; ci<C; ci++) {
                if (mat[ri][ci] == 1 && info.single == false) {
                    info.single = true;
                    info.rc = std::make_pair(ri, ci);
                } else if (mat[ri][ci] == 1) {
                    info = Info();
                    break;
                }
            }
        }
        
        int count=0;
        for (int ci=0; ci<C; ci++) {
            Info info;
            for (int ri=0; ri<R; ri++) {
                if (mat[ri][ci] == 1 && info.single == false) {
                    info.single = true;
                    info.rc = std::make_pair(ri, ci);
                } else if (mat[ri][ci] == 1) {
                    info = Info();
                    break;
                }
            }
            if (info.single && row_info[info.rc.first].single && info.rc == row_info[info.rc.first].rc) {
                count++;
            }
        }
        return count;
    }
};
