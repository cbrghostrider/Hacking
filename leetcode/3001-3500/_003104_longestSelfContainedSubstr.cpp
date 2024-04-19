class Solution {

// The idea here is that if we assume that a solution contains a given character (e.g. 'a'), 
// then it contains the entire substr from the earliest to the latest location containing 'a'.
// Let these locations be [pb_a, pe_a]. i.e ptr_begin_a, ptr_end_a
//
// Now this in turn transitively brings in other letters. e.g. 'b'
// So we can expand the interval to [min(pb_a, pb_b), max(pe_a, pe_b)]
// Note that 'b's interval isn't disjoint, since it occurred between 'a's start and end.
// This can only be done up to 26 times, once for each letter.
// In the end we are left with either the whole string (so no solution assuming 'a' is in the solution)
// Or a substr, which is one candidate we have found.
//
// Now we just repeat the above process, for starting assumptions picking each possible character one-by-one.
// In the end, we have explored the entire solution.
//
// As long as we are careful, each of the 26 starting solutions don't need to read each position in the string more than once.
// This is because when we extend the initial interval, we only extend it leftwards or rightwards contiguously, and only check those new locations.
// Thus the complexity is 26*O(n) = O(n)
//
// The only additional caveat happens when we find two (or more) independent such sequences, that are contiguous to each other.
// This is handled by the disjoint sets at the end of the main function, which tries to merge such sequences.
//

// The earliest and latest locations of a character.
// Note: Constant space.
unordered_map<char, int> earliest;
unordered_map<char, int> latest;

void populate_earliest_latest(const string& s) {
    for (int i=0; i<s.size(); i++) {
        char ch = s[i];
        if (earliest.find(ch) == earliest.end()) { earliest[ch] = i; }
        latest[ch] = i;
    }
}

void explore(const string& s, unordered_set<char>& exps, char seed, int& left, int& right) {    
    // printf("Exploring %c\n", seed);
    auto it = exps.find(seed);
    if (it != exps.end()) {
        return;
    }
    exps.insert(seed);

    // Explore this character.    
    int ch_left = earliest[seed], ch_right = latest[seed];
    int new_left = std::min(left, ch_left);
    int new_right = std::max(right, ch_right);
    int old_left = left, old_right = right;

    left = new_left;
    right = new_right;  

    // printf("Processing letter %c (%d, %d): old: (%d, %d), new (%d, %d); left=%d, right=%d\n", seed, ch_left, ch_right, old_left, old_right, new_left, new_right, left, right);

    // which new seeds are brought in?
    vector<char> seeds;
    for (int i=new_left; i<old_left; i++) {
        if (exps.find(s[i]) != exps.end()) continue;        
        seeds.push_back(s[i]);
    }
    for (int i=old_right+1; i<=new_right; i++) {
        if (exps.find(s[i]) != exps.end()) continue;        
        seeds.push_back(s[i]);
    }              
    for (char ch : seeds) {
        explore(s, exps, ch, left, right);
    }
}

// To deal with concatenations.
// O(1) space since there can be no more than 26 disjoint sets.
map<int, int> disjoints;

public:
    int maxSubstringLength(string s) {
        populate_earliest_latest(s);

        int best_len = -1;
        for (char seed : "abcdefghijklmnopqrstuvwxyz") {            
            unordered_set<char> exps;            
            int right = earliest[seed]-1, left = latest[seed]+1;
            explore(s, exps, seed, left, right);
            if (left == 0 && right == s.size()-1) {
                continue;  // no solution
            }
            disjoints[left] = right;
            best_len = std::max(best_len, right-left+1);
        }

        // See if we can extend the best_len by dealing with concatenations of independent but adjacent subsets.
        for (auto it = disjoints.begin(); it != disjoints.end(); it++) {
            
            int start = it->first, end = it->second;
            auto it2 = it;
            it2++;
            for (; it2 != disjoints.end(); it2++) {
                if (it2->first == end+1) {
                    end = it2->second;                
                }
            
                int new_len = end-start+1;
                if (best_len < new_len && new_len < s.size()) {
                    // printf("**** Found a new interval to combine: %d\n", new_len);
                    best_len = std::max(best_len, new_len);
                }
            }
            
        }
        return best_len;
    }
};
