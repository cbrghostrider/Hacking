class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int count = 0;
        for (int c=0; c<strs[0].size(); c++) {
            bool sorted = true;
            char last = strs[0][c];
            for (int r=1; r<strs.size(); r++) {
                if (last > strs[r][c]) {
                    sorted = false;
                    break;
                }
                last = strs[r][c];
            }
            if (!sorted) count++;
        }
        return count;
    }
};
