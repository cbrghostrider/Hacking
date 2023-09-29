class Solution {
public:
    int cost(const vector<int>& position, int chosen, int p) {
        return (std::abs(position[chosen] - position[p]) % 2 == 0 ? 0 : 1);
    }
    
    // O(n^2) time, O(1) space.
    int minCostToMoveChips2(vector<int>& position) {
        int min = std::numeric_limits<int>::max();
        for (int chosen=0; chosen<position.size(); chosen++) {
            int c = 0;
            for (int i=0; i<position.size(); i++) {
                c += cost(position, chosen, i);
            }
            if (c < min) min = c;
        }
        return min;
    }
    
    // O(n) time.
    // Imagine you move all odd valued position[i] to index 1 (which costs nothing, since that is even # of steps)
    // Similarly move all even valued position[i] to index 0 (for 0 total cost).
    // Now either we need to move the first stack of chips to the second, or the second to the first.
    // Ans is min of those.
    int minCostToMoveChips(vector<int>& position) {
        int odd = 0, even = 0;
        for (int v : position) {
            if (v % 2 == 0) {
                even ++;
            } else {
                odd++;
            }
        }
        return std::min(even, odd);
    }
};
