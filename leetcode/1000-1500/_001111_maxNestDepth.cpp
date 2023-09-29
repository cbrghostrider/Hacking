class Solution {
public:
    // O(n) space, O(n) time, greedy algorithm.
    vector<int> maxDepthAfterSplit(string seq) {
        int depth = 0;
        vector<int> depths(seq.size(), -1);
        for (int i=0; i<seq.size(); i++) {
            if (seq[i] == '(') {
                depths[i] = ++depth;
            } else {
                depths[i] = depth--;
            }
        }
        for (int& d : depths) {
            if (d%2 == 0) {d = 1;} else {d = 0;}
        }
        return depths;
    }
};
