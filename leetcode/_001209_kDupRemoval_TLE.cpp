class Solution {
    vector<bool> marks;
    string s;
    
    // moves s_ptr to the next unmarked location
    int fastForward(int s_ptr) {
        while (s_ptr < s.size() && marks[s_ptr] == true) {s_ptr++;}
        return s_ptr;
    }
    
    // rewind is called when a k-deletion has just occurred starting at s_ptr
    // we rewind s_ptr to the first index of the start of the "last common bunch" before s_ptr.
    int rewind(int s_ptr) {
        while (s_ptr >=0 && marks[s_ptr]) {
            s_ptr--;
        }
        if (s_ptr == -1) {  // this is actually a fast-forward
            return fastForward(0);
        }
        
        int last_unmarked = s_ptr;
        int e_ptr = s_ptr;
        
        while (e_ptr >= 0 && (s[e_ptr] == s[s_ptr] || marks[e_ptr])) { 
            if (!marks[e_ptr]) {last_unmarked = e_ptr;}
            e_ptr--; 
        }
        if (e_ptr == -1) {
            if (last_unmarked == -1) return fastForward(s_ptr);
            else return last_unmarked;
        }
        return e_ptr + 1;
    }
    
public:
    // O(n^2) time, O(n) space.
    string removeDuplicates(string str, int k) {
        s = str;
        marks = vector<bool>(s.size(), false);
        
        int s_ptr=0;
        while (s_ptr < s.size()) {
            int e_ptr = s_ptr;
            int len=0;
            while (e_ptr < s.size() && len < k && 
                   (marks[e_ptr] == true || s[s_ptr] == s[e_ptr])) {
                if (marks[e_ptr] == false) {len++;}
                e_ptr++;
            }
            if (e_ptr == s.size() && len < k) break;
            
            // Nothing to delete.
            if (len < k) {
                s_ptr = e_ptr;
                continue;
            }
            
            for (int i=s_ptr; i<e_ptr; i++) {
                marks[i] = true;
            }
            
            s_ptr = rewind(s_ptr);
        }
        
        string ans;
        for (int i=0; i<s.size(); i++) {
            if (!marks[i]) {ans.push_back(s[i]);}
        }
        return ans;
    }
};
