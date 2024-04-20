class Solution {

bool should_prune(const set<int>& leftover, const vector<int>& seq, int next_item) {
    if (seq.size() >= 1) {
        // All the bad combinations are detected here.
        if (seq.back() == 1 && next_item == 9 && leftover.find(5) != leftover.end()) return true;
        if (seq.back() == 9 && next_item == 1 && leftover.find(5) != leftover.end()) return true;
        if (seq.back() == 2 && next_item == 8 && leftover.find(5) != leftover.end()) return true;
        if (seq.back() == 8 && next_item == 2 && leftover.find(5) != leftover.end()) return true;
        if (seq.back() == 3 && next_item == 7 && leftover.find(5) != leftover.end()) return true;
        if (seq.back() == 7 && next_item == 3 && leftover.find(5) != leftover.end()) return true;
        if (seq.back() == 4 && next_item == 6 && leftover.find(5) != leftover.end()) return true;
        if (seq.back() == 6 && next_item == 4 && leftover.find(5) != leftover.end()) return true;        
        if (seq.back() == 1 && next_item == 3 && leftover.find(2) != leftover.end()) return true;
        if (seq.back() == 3 && next_item == 1 && leftover.find(2) != leftover.end()) return true;
        if (seq.back() == 9 && next_item == 3 && leftover.find(6) != leftover.end()) return true;
        if (seq.back() == 3 && next_item == 9 && leftover.find(6) != leftover.end()) return true;
        if (seq.back() == 7 && next_item == 9 && leftover.find(8) != leftover.end()) return true;
        if (seq.back() == 9 && next_item == 7 && leftover.find(8) != leftover.end()) return true;
        if (seq.back() == 7 && next_item == 1 && leftover.find(4) != leftover.end()) return true;
        if (seq.back() == 1 && next_item == 7 && leftover.find(4) != leftover.end()) return true;
    }
    return false;
}

int recurse(set<int>& leftover, vector<int>& seq, int& dots_to_pick) {
    if (dots_to_pick == 0) {
        return 1;  // This counts as one combination.
    }
    
    int my_count=0;
    set<int> snapshot = leftover;
    for (int dot : snapshot) {                
        if (should_prune(leftover, seq, dot)) {
              // bad combination
            continue; 
        }
        leftover.erase(dot);
        seq.push_back(dot);        
        dots_to_pick--;
        
        my_count += recurse(leftover, seq, dots_to_pick);

        dots_to_pick++;
        seq.pop_back();        // remove dot
        leftover.insert(dot);  // put it back
    }

    return my_count;
}

public:
    int numberOfPatterns(int m, int n) {
        if (m > n) std::swap(m, n);

        int grand_count=0;
        for (int d=m; d<=n; d++) {
            set<int> dots;
            for (int i=1; i<=9; i++) { dots.insert(i); }    
            vector<int> seq;        
            int dtp = d;
            int count = recurse(dots, seq, dtp);
            grand_count += count;
        }
        return grand_count;
    }
};
