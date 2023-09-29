class Solution {
public:
    int maxDepth(string s) {
        int max=0;
        int depth = 0;
        for (char ch : s) {
            if (ch == '(') {
                depth++;
                if (depth > max) {max = depth;}
            } else if (ch == ')') {
                depth--;
            }
        }
        return max;
    }
};
