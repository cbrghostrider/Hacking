class Solution {
    // Two pointers solution
    // Maintain a left and right pointer, which only advance rightwise.
    // Also maintain a hashtable, which tells us counts of unique chars seen so far.
    // Initially both ptrs set to 0. Right pointer advances.
    // At some point, the diff between right and left exceeds minSize, so we start recording counts of substrs.
    // At some future point, either maxSize or MaxLetters is violated.
    // When this happens, reset state. i.e. right=left, left++, 
    // then the process renews from the new position.
public:
    // O(n^2) time, O(n) space.
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int left=0, right=-1;
        unordered_map<char, int> htable;
        unordered_map<string, int> ss_counts;
        
        while (left < s.size()) {
            
            // Decide whether right advances
            if (right + 1 < s.size() && right-left+1 < maxSize) {
                if (htable.find(s[right+1]) != htable.end()) {
                    htable[s[right+1]]++;
                    right++;
                } else {
                    if (htable.size() < maxLetters) {
                        htable[s[right+1]] = 1;
                        right++;
                    } else {  // can't advance right after all, advance left instead
                        htable.clear();
                        right=left;
                        left++;
                    }
                }
            } else {  // advance left if right can't advane
                htable.clear();
                right = left;
                left++;
            }
            
            if (right-left+1 <= maxSize && right-left+1 >= minSize) {
                ss_counts[s.substr(left, right-left+1)]++;
            }
        }
        int max=0;
        for (const auto& kv : ss_counts) {
            if (kv.second > max) {
                max = kv.second;
            }
        }                  
        return max;
    }
};
