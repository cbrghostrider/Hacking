class Solution {
public:
    enum Direction {Down, Up};
    
    typedef pair<int, Direction> t_Index;
    
    t_Index getNextIndex(const t_Index& curInd, const int size) {
        if (size <= 1) return curInd;
        
        if (curInd.second == Down) {
            if (curInd.first == size-1) {
                return make_pair(curInd.first - 1, Up);
            } else {
                return make_pair(curInd.first + 1, curInd.second);
            }
        } else {
            if (curInd.first == 0) {
                return make_pair(1, Down);
            } else {
                return make_pair(curInd.first - 1, curInd.second);
            }
        }
    }
    
    string convert(string s, int nRows) {
        if (nRows <= 1 ) {
            return s;
        }
        
        vector<string> rows(nRows, "");
        t_Index ind(0, Down);
        
        for (auto it = s.begin(); it != s.end(); it++) {
            rows[ind.first] = rows[ind.first] + (*it);
            ind = getNextIndex(ind, nRows);
        }
        
        string ret;
        for_each (rows.begin(), rows.end(), [&ret] (const string& str) -> void {
            ret += str;
        });
        
        return ret;
    }
};
