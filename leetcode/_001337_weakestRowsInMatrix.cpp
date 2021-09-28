class Solution {
public:
    // binary search to find index of rightmost 1 in row
    int findRightmostIndex(const vector<int>& row, int left, int right) {
        if (right - left <= 1) {
            if (row[right] == 1) {
                return right;
            }
            if (row[left] == 1) {
                return left;
            }
            return -1;
        }
        
        int mid = ((long long)left + right)/2;
        if (row[mid+1] == 1) {
            return findRightmostIndex(row, mid+1, right);
        } else if (row[mid] == 1) {
            return mid;
        }
        return findRightmostIndex(row, left, mid-1);
    }
    
    int numSoldiers(const vector<vector<int>>& mat, int index) {
        int val = findRightmostIndex(mat[index], 0, mat[index].size()-1);
        if (val == -1) {
            return 0;
        }
        return val + 1;
    }
    
    struct RowInfo {
        int index = -1;
        int soldiers = 0;
    };
    
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<RowInfo> info(mat.size(), RowInfo());
        for (int index=0; index < mat.size(); index++) {
            info[index] = {index, numSoldiers(mat, index)};
        }
        
        std::sort(info.begin(), info.end(), [](const RowInfo& left, const RowInfo& right) -> bool {
            if (left.soldiers < right.soldiers) {
                return true;
            } else if (left.soldiers == right.soldiers) {
                return (left.index < right.index);
            }
            return false;
        });
        
        vector<int> indices(k, -1);
        for (int i=0; i<k; i++) {
            indices[i] = info[i].index;
        }
        return indices;
    }
};
