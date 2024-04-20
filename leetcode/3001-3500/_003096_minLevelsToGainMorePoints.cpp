class Solution {
public:
    int minimumLevels(vector<int>& possible) {
        vector<int> pfsum_alice(possible.size(), 0);
        vector<int> pfsum_bob(possible.size(), 0);
        int sum=0;
        for (int i=0; i<possible.size(); i++) {
            sum += (possible[i] ? 1 : -1);
            pfsum_alice[i] = sum;
        }
        sum=0;
        for (int i=possible.size()-1; i>=0; i--) {
            sum += (possible[i] ? 1 : -1);
            pfsum_bob[i] = sum;
        }
        // if (pfsum_bob[0] < 0) {return 0;}  // Alice should play no levels.
        for (int i=0; i<possible.size()-1; i++) {
            if (pfsum_alice[i] > pfsum_bob[i+1]) {
                return i+1;
            }
        }
        // if (pfsum_alice.back() > 0) {return possible.size();}  // Alice should play all levels.
        return -1;
    }
};
