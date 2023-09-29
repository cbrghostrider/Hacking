// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    //will return whether string can be made palindrome at that pivot (from the end)
    //if so, will make it a palindrome
    bool isPalindrome (string& sp, int pivot, bool isEven) {
        if (pivot == 0) {
            string attach = sp.substr(1);
            std::reverse(attach.begin(), attach.end());
            sp = attach + sp;
            return true;
        }
        int i=pivot, j = isEven ? pivot-1 : pivot;
        for (; i<sp.length() && j >= 0; i++, j--) {
            if (sp[i] != sp[j]) { return false;} 
        }
        string attach = sp.substr(i);
        std::reverse(attach.begin(), attach.end());
        sp = attach + sp;
        return true;
    }
    
public:
    string shortestPalindrome(string s) {
        if (s.length() <= 1) return s;
        bool isEven = (s.length() % 2) == 0;

        for (int pivot = s.length()/2; pivot>=0; ) {
            string sp = s;
            if (isPalindrome(sp, pivot, isEven)) return sp;
            if (isEven) pivot--;
            isEven = !isEven;
        }
        assert(0);     
    }
};
