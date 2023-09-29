/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
    BinaryMatrix *bm=nullptr;
    int R, C;
    
    bool hasColOne(int col) {
        for (int r=0; r<R; r++) {
            if (bm->get(r, col) == 1) return true;
        }
        return false;
    }
    
    int search(int left, int right) {
        if (left == right) {
            if (hasColOne(left)) return left; else return -1;
        }
        if (left + 1 == right) {
            if (hasColOne(left)) return left;
            if (hasColOne(right)) return right;
            return -1;
        }
        int mid = (left+right)/2;
        if (hasColOne(mid)) {
            return search(left, mid);
        }
        return search(mid, right);
    }
public:
    // O(R log C) time, O(1) space.
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        auto dim = binaryMatrix.dimensions();
        R=dim[0]; C=dim[1];
        bm = &binaryMatrix;
        return search(0, C-1);
    }
};
