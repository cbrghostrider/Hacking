class Solution {
public:
    string breakPalindrome(string palindrome) {
        if (palindrome.size() <= 1) return "";
        if (palindrome[0] != 'a') {
            palindrome[0] = 'a';
            return palindrome;
        }
        // find first occurrence of not 'a'
        int ptr=0;
        while (ptr < palindrome.size() && palindrome[ptr] == palindrome[0]) {ptr++;}
        if (ptr == palindrome.size()) {
            palindrome[palindrome.size()-1] = 'b';
            return palindrome;
        }
        
        if (!(palindrome.size() % 2 != 0 && ptr == palindrome.size()/2)) {
            palindrome[ptr] = 'a';
            return palindrome;
        }
        palindrome[palindrome.size()-1] = 'b';
        return palindrome;
    }
};
