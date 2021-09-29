class Solution {
public:
    
    // binary search within a row to find number of negatives
    int countRowNegatives(const vector<int>& row, int left, int right) {
        if (right - left <= 1) {
            int negatives = 0;
            if (row[left] < 0) negatives++;
            if (row[right] < 0 && left != right) negatives++;
            return negatives;
        }
        
        int mid = ((long long)left + right) / 2;
        if (row[mid-1] < 0) {
            return countRowNegatives(row, left, mid-1) + 1 + (right - mid);
        } else if (row[mid] < 0) {
            return 1 + (right - mid);
        }
        return countRowNegatives(row, mid+1, right);
    }
    
    // mlogn solution
    int countNegativesMlogN(vector<vector<int>>& grid) {
        int negatives = 0;
        for (int m=0; m<grid.size(); m++) {
            negatives += countRowNegatives(grid[m], 0, grid[m].size()-1);
        }
        return negatives;
    }
    
    int countNegatives(vector<vector<int>>& grid) {
        return countNegativesMlogN(grid);
    }
};
