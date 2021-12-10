class Solution {
public:
    // O(n) time, O(n) space.
    int minimumSwap(string s1, string s2) {
        unordered_map<char, int> f1, f2;
        for (char ch : s1) {f1[ch]++;}
        for (char ch : s2) {f2[ch]++;}
        if ((f1['x'] + f2['x']) % 2 != 0) return -1;
        if ((f1['y'] + f2['y']) % 2 != 0) return -1;
        
        int mismatches=0, mismatches_x=0, mismatches_y=0;
        for (int i=0; i<s1.size(); i++) {
            if (s1[i] == s2[i]) continue;
            mismatches++;
            if (s1[i] == 'x') mismatches_x++;
            if (s1[i] == 'y') mismatches_y++;
        }
        
        // every x in s1 is mismatched with a y in s2, and vice versa.
        // one could use a single move to eliminate 2 mismatches if you had s1="xx" s2="yy"
        // but need 2 moves if you had s1="xy" and s2="yx"
        
        int single_move = mismatches_x/2 + mismatches_y/2;
        int double_move = (mismatches - single_move*2);
        return single_move + double_move;
    }
};
