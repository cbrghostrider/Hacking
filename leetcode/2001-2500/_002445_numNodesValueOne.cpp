class Solution {
    // Simply inc the number of flips, which will be applied lazily.
    // This is because if a tree is flipped an even number of times, nothing changes.
    // So we want to avoid doing wasteful work.
    vector<int> flips;

    // from_above denotes the recursive flips accumulated from above.
    // returns the total number of 1's in this subtree.
    int lazy_flip(int root, int from_above) {
        if (root >= flips.size()) return 0;
        int left = 2*root + 1;
        int right = 2*root + 2;
        int my_flips = from_above + flips[root];
        int my_val = my_flips % 2;
        my_val += lazy_flip(left, my_flips);
        my_val += lazy_flip(right, my_flips);
        return my_val;
    }
public:
    // Complexity = O(m + log n)
    // m = |queries|
    // n = |tree|
    int numberOfNodes(int n, vector<int>& queries) {
        // nodes = vector<bool>(n, false);
        flips = vector<int>(n, 0);
        for (int query : queries) {
            // Convert to 0-based index and apply lazy flip.
            flips[query-1]++;
        }
        return lazy_flip(0, 0);
    }
};
