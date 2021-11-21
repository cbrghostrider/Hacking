class Solution {
public:
    int minimumMoves(string s) {
        int s_ptr=0, moves=0;
        while (s_ptr < s.size()) {
            if (s[s_ptr] == 'X') {
                moves++;
                s_ptr += 3;
            } else {
                s_ptr++;
            }
        }
        return moves;
    }
};
