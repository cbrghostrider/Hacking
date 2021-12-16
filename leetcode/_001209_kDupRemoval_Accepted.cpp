// 
// Note: This algorithm is correct and efficient [O(n) runtime, and O(n) space].
//       The solution runs within time limits and is accepted.
//
// However it is a pretty convoluted algorithm, and quite intricate.
//
// The high-level logic is as follows:
// 1. We find the first "bunch" of k-common letters. 
//    This is done using the two-pointers method: s_ptr and e_ptr in the main function.
// 2. Then we delete them.
// 3. Now we "rewind" the s_ptr so that it points to the "start" of the 
//    last common bunch of letters (may be 1-sized bunch).
//    Note further that the "rewind" may actually also involve a "fastforward" instead
//    if we find that all the previous indices are marked.
//
//  In order to avoid constructing the string again and again, we maintain a 
//  hashtable of deleted indices. We delete these letters at the end.
//
//  All this so far is in common with the algorithm before (that got TLE).
//
//  Now, in order to avoid TLE, we DO NOT REWIND THE e_ptr, we only rewind the s_ptr!!!!!!!
//
//  We introduce a new indices vector to instead note the new "marked" positions.
//  We maintain len and indices across the rewind call (this gets really intricate).
//  In the end, it all miraculously worked out, and the solution got accepted. 
//
//  \_ o _/
//
// Also note that the degenerate test case is having a (10^5 / 2) string of concat a..z
// repeatedly. Then reverse this and concat it with the original to get a (10^5) string.
// Note that this is a perfect palindrome, with each letter different from the previous, 
// EXCEPT for the middle 2 letters. These when deleted, give us a SIMILAR palindrome again.
//
// Now using k=2, we have to repeatedly delete the middle two letters.
//
// SINCE WE MADE THE BRILLIANT DECISION NOT TO REWIND THE e_ptr, and only the s_ptr, 
// we don't end up walking the entire string again and again.
//

class Solution {
    unordered_set<int> marks;  // hash table of indices marked
    string s;
    int K=0;
    
    bool isMarked(int index) {
        return (marks.find(index) != marks.end());
    }
    
    void mark(int index) {
        marks.insert(index);
    }
    
    // moves s_ptr to the next unmarked location
    int fastForward(int s_ptr) {
        while (s_ptr < s.size() && isMarked(s_ptr)) {s_ptr++;}
        return s_ptr;
    }
    
    // rewind is called when a k-deletion has just occurred starting at s_ptr
    // we rewind s_ptr to the first index of the start of the "last common bunch" before s_ptr.
    // MODIFIED ALGORITHM: now returns the indices of the last bunch, modifies s_ptr, len in place
    vector<int> rewind(int& s_ptr, int& len) {
        while (s_ptr >=0 && isMarked(s_ptr)) {
            s_ptr--;
        }
        if (s_ptr == -1) {  // this is actually a fast-forward
            s_ptr = fastForward(0);
            len = 0;
            return {s_ptr};
        }
        
        int last_unmarked = s_ptr;
        int e_ptr = s_ptr;
        len=0;
        
        vector<int> indices;
        
        while (e_ptr >= 0 && len < K && (s[e_ptr] == s[s_ptr] || isMarked(e_ptr))) { 
            if (!isMarked(e_ptr)) {
                last_unmarked = e_ptr;
                indices.push_back(e_ptr);
                len++;
            }
            e_ptr--; 
        }
        if (e_ptr == -1) {
            if (last_unmarked == -1) {
                s_ptr = fastForward(s_ptr);
                len = 0;
                return {s_ptr};
            } else {
                s_ptr = last_unmarked;
                return indices;
            }
        }
        s_ptr = last_unmarked;
        return indices;
    }
    
public:
    // O(n) time, O(n) space.
    string removeDuplicates(string str, int k) {
        s = str;
        K = k;
        
        // Modified this part too
        int s_ptr=0;
        int e_ptr = s_ptr;
        int len=0;
        vector<int> indices;
        while (s_ptr < s.size()) {
            while (e_ptr < s.size() && len < K && 
                   (isMarked(e_ptr) || s[s_ptr] == s[e_ptr])) {
                if (!isMarked(e_ptr)) {
                    indices.push_back(e_ptr);
                    len++;
                }
                e_ptr++;
            }
            if (e_ptr == s.size() && len < k) break;
            
            // Nothing to delete.
            if (len < K) {
                s_ptr = e_ptr;
                len = 0;
                indices.clear();
                continue;
            }
            
            for (int i: indices) {
                marks.insert(i);
            }
            
            // Modified this part too
            indices = rewind(s_ptr, len);
        }
        
        string ans;
        for (int i=0; i<s.size(); i++) {
            if (!isMarked(i)) {ans.push_back(s[i]);}
        }
        return ans;
    }
};

