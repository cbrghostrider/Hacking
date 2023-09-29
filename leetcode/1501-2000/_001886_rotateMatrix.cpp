class Solution {
    //////////////////////////////////////////////////////////////////////////////////
    // This first solution is from misreading the question. Specifically, it does not
    // account for the "90 degree increment" part. It solves the question for any 
    // general rotation, and different "rings" can have different rotations. I don't
    // know why I misread it like this. \_ o _/
    //////////////////////////////////////////////////////////////////////////////////
    
    // Gets next coord in the ring, given n (mat len) and given k (ring NUMBER).
    // This coord is "x places" away; moving clockwise.
    std::pair<int, int> nextRingCoord(std::pair<int, int> coord, int n, int k, int x) {
        if (k < 0 || n <= 0 || x <= 0) return coord;
        int row = coord.first, col = coord.second;
        const int COL_RIGHT = n-1-k, COL_LEFT = k;
        const int ROW_TOP = k, ROW_BOTTOM = n-1-k;
        while (x > 0) {
            if (row == ROW_TOP && col < COL_RIGHT) {  // move right
                int diff = COL_RIGHT - col;
                if (x <= diff) return std::make_pair(row, col+x);
                x -= diff;
                col = COL_RIGHT;
            } else if (row == ROW_BOTTOM && col > COL_LEFT) {
                int diff = col - COL_LEFT;
                if (x <= diff) return std::make_pair(row, col-x);
                x -= diff;
                col = COL_LEFT;
            } else if (col == COL_LEFT && row > ROW_TOP) {
                int diff = row - ROW_TOP;
                if (x <= diff) return std::make_pair(row-x, col);
                x -= diff;
                row = ROW_TOP;
            } else if (col == COL_RIGHT && row < ROW_BOTTOM) {
                int diff = ROW_BOTTOM-row;
                if (x <= diff) return std::make_pair(row+x, col);
                x -= diff;
                row = ROW_BOTTOM;
            }
        }
        // should not happen
        return std::make_pair(-1, -1);
    }
    
    unsigned long constructBinary(const vector<vector<int>>& mat, std::pair<int, int> start, int n, int k) {
        const int SZ = mat.size() - k*2;
        const int ELEMS = 4*(SZ-1);
        unsigned long ans = 0;
        for (int e=0; e<ELEMS; e++) {
            ans <<= 1;
            ans |= mat[start.first][start.second];
            start = nextRingCoord(start, n, k, 1);
        }
        return ans;
    }
    
    // Compares the kth rings for mat and target, trying all rotations.
    // Returns the number of rotations needed to match, or -1 if not possible.
    // construct 64-bit binary numbers, and compare rotations
    int compareRings(const vector<vector<int>>& mat, const vector<vector<int>>& target, int k) {
        if (k > mat.size()/2) return -1;
        
        // Rotations go from [0, 4*(sz-1)] where sz is size of each length of the ring
        const int N = mat.size();
        const int SZ = mat.size() - k*2;
        const int ELEMS = 4*(SZ-1);
        std::pair mat_coord = std::make_pair(k, k);
        unsigned long matrix_num = constructBinary(mat, mat_coord, N, k);
        for (int r=0; r<ELEMS; r++) {
            std::pair tgt_coord = nextRingCoord(mat_coord, N, k, r);
            unsigned long target_num = constructBinary(target, tgt_coord, N, k);
            if (target_num == matrix_num) return r;
        }
        return -1;
    }
    
public:
    // Solution for the misread problem.
    // Leaving it in because it is interesting.
    bool findRotation2(vector<vector<int>>& mat, vector<vector<int>>& target) {
        if (mat.size() <= 1) return mat[0][0] == target[0][0];
        int num_rings = mat.size()/2;
        for (int k=0; k<num_rings; k++) {
            int rot = compareRings(mat, target, k);
            if (rot == -1) return false;
        }
        if (mat.size()%2) {
            int mid = mat.size()/2;
            return mat[mid][mid] == target[mid][mid];
        }
        return true;
    }
    
    // This is the correct solution to the stated problem.
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        const int N = mat.size();
        bool match = true;
        for (int rm=0, rt=0; rm<N && rt<N; rm++, rt++) {
            for (int cm=0, ct=0; cm<N && ct<N; cm++, ct++) {
                if (mat[rm][cm] != target[rt][ct]) {
                    match = false;
                    break;
                }
            }
        }
        if (match) return true;
        
        match = true;
        for (int rm=0, ct=N-1; rm<N && ct>=0; rm++, ct--) {
            for (int cm=0, rt=0; cm<N && rt<N; cm++, rt++) {
                if (mat[rm][cm] != target[rt][ct]) {
                    match = false;
                    break;
                }
            }
        }
        if (match) return true;
        
        match = true;
        for (int rm=0, rt=N-1; rm<N && rt >= 0; rm++, rt--) {
            for (int cm=0, ct=N-1; cm<N && ct>=0; cm++, ct--) {
                if (mat[rm][cm] != target[rt][ct]) {
                    match = false;
                    break;
                }
            }
        }
        if (match) return true;

        match = true;
        for (int rm=0, ct=0; rm<N && ct <N; rm++, ct++) {
            for (int cm=0, rt=N-1; cm<N && rt>=0; cm++, rt--) {
                if (mat[rm][cm] != target[rt][ct]) {
                    match = false;
                    break;
                }
            }
        }
        return match;
    }
};
