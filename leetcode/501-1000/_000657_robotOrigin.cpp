class Solution {
public:
    bool judgeCircle(string moves) {
        int ups=0, downs=0, rights=0, lefts=0;
        for (char ch : moves) {
            switch (ch) {
                case 'U':
                    ups++; break;
                case 'D':
                    downs++; break;
                case 'L':
                    lefts++; break;
                case 'R':
                    rights++; break;
            }
        }
        return (ups == downs && lefts == rights);
    }
};
