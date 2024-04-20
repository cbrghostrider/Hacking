class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        vector<bool> possible(7, false);

        for (int i=1; i<7; i++) {
            bool poss = true;
            for (int j=0; j<tops.size(); j++) {
                if (tops[j] != i && bottoms[j] != i) {
                    poss = false;
                    break;
                }
            }
            possible[i] = poss;
        }

        int ret=std::numeric_limits<int>::max();
        for (int val=1; val<7; val++) {
            if (!possible[val]) continue;
            int flip_tops=0;
            int flip_bottoms=0;
            for (int i=0; i<tops.size(); i++) {
                if (tops[i] != val) flip_tops++;
                if (bottoms[i] != val) flip_bottoms++;
            }
            ret = std::min(ret, std::min(flip_tops, flip_bottoms));
        }
        if (ret == std::numeric_limits<int>::max()) return -1;
        return ret;
    }
};
