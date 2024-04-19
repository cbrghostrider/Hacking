class Solution {

// Memoization table.
std::unordered_map<size_t, int> htable;
size_t memoize(char left_c, int left_ind, char right_c, int right_ind) {
    size_t val = (((size_t)left_c) << 24);
    val |= (((size_t)right_c) << 16);
    val |= (((size_t)left_ind) << 8);
    val |= (((size_t)right_ind));
    return val;
}

public:

    // left_c is the leftmost char in the palindrome so far
    // left_ind is the left side recursion we are considering (independent from above).
    // similarly for right_c, and right_ind
    int grow(const string& s, char left_c, int left_ind, char right_c, int right_ind) {
        if (left_ind < 0 || right_ind >= s.size()) return 0;

        size_t memo = memoize(left_c, left_ind, right_c, right_ind);
        if (htable.find(memo) != htable.end()) return htable[memo];

        int cand_0=0;
        if (s[left_ind] != left_c && right_c != s[right_ind] && s[left_ind] == s[right_ind]) {
            // keep left, keep right
            cand_0 = 2 + grow(s, s[left_ind], left_ind-1, s[right_ind], right_ind+1);
        }

        // drop left, keep right
        int cand_1 = grow(s, left_c, left_ind-1, right_c, right_ind);

        // keep left, drop right
        int cand_2 = grow(s, left_c, left_ind, right_c, right_ind+1);

        // drop left, drop right
        int cand_3 = grow(s, left_c, left_ind-1, right_c, right_ind+1);

        int best = std::max(std::max(cand_0, cand_1), std::max(cand_2, cand_3));
        htable[memo] = best;
        return best;
    }

    int longestPalindromeSubseq(string s) {
        int best_len=0;
        // We will grow the palindromes.
        for (int i=0; i<s.size(); i++) {
            char left_c = s[i];
            for (int j=i+1; j<s.size(); j++) {
                char right_c = s[j];
                if (s[i] != s[j]) continue;

                // Found a starting set (left_c, right_c).
                int my_len = 2 + grow(s, left_c, i-1, right_c, j+1);
                best_len = std::max(my_len, best_len);
            }
        }
        return best_len;
    }
};
