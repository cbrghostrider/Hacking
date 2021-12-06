class Solution {
public:
    // O(n) time, O(1) space.
    int minAddToMakeValid(string s) {
        int count=0;
        int open_count=0;
        for (char ch : s) {
            if (ch == '(') {
                open_count++;
            } else {  // ch == ')'
                if (open_count <= 0) { count++; }
                else { open_count--; }
            }
        }
        return count + open_count;
    }
};
