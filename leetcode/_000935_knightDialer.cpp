class Solution {
    unordered_map<int, unordered_set<int>> moves = {
        {0, {4, 6}}, {1, {6, 8}}, {2, {7, 9}}, {3, {4, 8}},
        {4, {0, 3, 9}}, {5, {}}, {6, {0, 1, 7}}, {7, {2, 6}}, 
        {8, {1, 3}}, {9, {2, 4}}
    };
    
public:
    // O(n) time, O(1) space.
    // The inner two loops are only doing constant amount of work.
    int knightDialer(int n) {
        if (n == 1) return 10;
        
        // stores for val->how many unique phone numbers
        // stores (modulo 10^9 + 7)
        // Only stores the last value (i-1), and it is used during iteration i
        // iteration 0 is base case (n==1)
        //
        // We will IGNORE 5, since it leads to NOWHERE, and we need numbers of exactly n digits
        //
        // This vector stores num combos ending in digit i.
        vector<int> combos(10, 1);
        combos[5] = 0;  // ignore this sucker.
        
        for (int ni=2; ni<=n; ni++) {
            vector<int> new_combos(10, 0);
            for (int dig=0; dig<10; dig++) {
                for (int end : moves[dig]) {
                    new_combos[end] += combos[dig];
                    new_combos[end] %= 1000000007;
                }
            }
            combos = new_combos;
        }
        
        return std::accumulate(combos.begin(), combos.end(), 0, [](int acc, int val) -> int {
            acc += val;
            acc %= 1000000007;
            return acc;
        });
    }
};
