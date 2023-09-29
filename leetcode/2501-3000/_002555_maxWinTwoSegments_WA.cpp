// WA
// 68/72 test cases pass.
// There's some bug somewhere...
//
// Turns out the basic assumption itself is incorrect.
// Thanks to counter-example constructed by grantas0612 comment below:
//
// I assume that you're trying to find a best win for a single segment,
// and then another best win from the prizes excluding the best segment.
// But it is not guaranteed that the best single segment is included in
// the two best combined segments. For example, with
// prizePositions = [2, 6, 7, 9, 11, 14] and k = 5,
// the best single segment is [6, 7, 9, 11],
// while the best two combined segments are [2, 6, 7] and [9, 11, 14]
//
// Note also that:
// Two adjacent k-windows is not the same as
// One 2k-window
// This makes it not possible to consider pick_2k as another choice.
// The same counter-example as above proves this.
class Solution {
    struct Info {
        int num_prizes=0;
        // pp[end] - pp[start] <= k
        int start=-1;  // inclusive (the index in the array)
        int end=-1;    // inclusive (the index in the array)
        void print() {
            printf("Info: num=%d; (%d, %d)\n", num_prizes, start, end);
        }
    };

    bool is_valid(const vector<int>& pp, int start, int end, int k) {
        return (pp[end]-pp[start] <= k);
    }
    // Returns the max number of prizes won with segment k in the given index bounds.
    // Along with that it also returns the indices where this best occurs.
    //
    // i.e. we can only consider index "start" upto index "end".
    // This function is called up to 3 times.
    Info optimize(const vector<int>& pp, int start, int end, int k) {
        if (end < 0 || start >= pp.size()) return Info();
        if (is_valid(pp, start, end, k)) {
            Info info = {end-start+1, start, end};
            return info;
        }
        // first and last are also indices.
        int first=start, last=start;
        Info best;
        while (last <= end) {
            // grow the segment; only affects "last"
            while (last <= end && is_valid(pp, first, last, k)) {
                Info cur = {last-first+1, first, last};
                if (best.num_prizes < cur.num_prizes) {
                    best = cur;
                }
                last++;
            }            
            if (last > end) {break;}

            // shrink the segment, only affects "first"
            while (first <= last && !is_valid(pp, first, last, k)) {
                first++;
            }
        }
        return best;
    }
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        Info pick1 = optimize(prizePositions, 0, prizePositions.size()-1, k);
        Info pick_left = optimize(prizePositions, 0, pick1.start-1, k);
        Info pick_right = optimize(prizePositions, pick1.end+1, prizePositions.size()-1, k);
        pick1.print();
        pick_left.print();
        pick_right.print();
        int prizes_left = pick1.num_prizes + pick_left.num_prizes;
        int prizes_right = pick1.num_prizes + pick_right.num_prizes;
        return std::max(prizes_left, prizes_right);
    }
};
