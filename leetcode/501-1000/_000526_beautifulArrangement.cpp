class Solution {
public:

    int countArrangement(int n) {
        populateValid(n);
        set<int> exclude;
        int ans = waysRecurse(n, exclude);
        return ans;
    }
    
    unordered_map<int, set<int>> valid;
    
    // populates for each number, what are the valid positions that it can appear at.
    void populateValid(int n) {
        for (int num=1; num<=n; num++) { // each number, check each position
            for (int pos=1; pos<=n; pos++) {
                if ((num % pos == 0) || (pos % num == 0)) {
                    valid[num].insert(pos);
                }
            }
        }
        auto some = valid;
        return;
    }
    
    // Try various "valid" ways to fit number "try_num" in a position.
    // But don't put it in positions that are in the exclude set.
    int waysRecurse(int try_num, set<int>& exclude) {
        if (try_num == 1) return 1;  // by the time we get to 1, only 1 position is left.
        
        set<int> choices;
        std::set_difference(valid[try_num].begin(), valid[try_num].end(), exclude.begin(), exclude.end(), 
                           std::inserter(choices, choices.end()));
        
        int total=0;
        for (int num : choices) {
	    // Classic backtracking algorithm here.
            exclude.insert(num);
            total += waysRecurse(try_num-1, exclude);
            exclude.erase(num);
        }
        return total;
    }
};
