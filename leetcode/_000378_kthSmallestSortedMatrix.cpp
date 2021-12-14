class Solution {
    struct Info {
        int row=0;
        int col=0;
        int val=0;
    };
    int R, C;   
        
    std::function<bool(const Info& lhs, const Info& rhs)> comp = [](const Info& lhs, const Info& rhs) -> bool {
        return lhs.val > rhs.val;
    };
    std::priority_queue<Info, vector<Info>, decltype(comp)> min_heap;
    
    string sig(int row, int col) {return std::to_string(row) + "-" + std::to_string(col);}
    bool handled(int row, int col) {return coords.find(sig(row, col)) != coords.end();}
    

    std::unordered_set<string> coords;
    
public:
    // Note that due to the way we are inserting elements in the heap, only (R+C) elements can be present at a time.
    // O(R+C) space, O((R+C) log (R+C)) time.
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        R = matrix.size();
        C = matrix[0].size();
        if (k > R*C) return -1;      

        min_heap = std::priority_queue<Info, vector<Info>, decltype(comp)>(comp);
        
        min_heap.push({0, 0, matrix[0][0]});
        coords.insert(sig(0, 0));
        
        auto& dbg = min_heap;
        while (k >= 2) {
            Info info = min_heap.top();
            min_heap.pop();
            if (info.col != C-1 && !handled(info.row, info.col+1)) {
                min_heap.push({info.row, info.col+1, matrix[info.row][info.col+1]});
                coords.insert(sig(info.row, info.col+1));
            }
            if (info.row != R-1 && !handled(info.row+1, info.col)) {
                min_heap.push({info.row+1, info.col, matrix[info.row+1][info.col]});
                coords.insert(sig(info.row+1, info.col));                
            }
            k--;
        }
        return min_heap.top().val;
    }
};
