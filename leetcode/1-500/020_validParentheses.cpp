// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    unordered_map<char, char> complement = {{')', '('}, {']', '['}, {'}', '{'}};
public:
    bool isValid(string s) {
        vector<char> stack;
        for (const char& ch : s) {
            if (ch == ')' || ch == ']' || ch == '}') {
                if (stack.empty()) return false;
                if (stack.back() != complement[ch]) return false;
                stack.pop_back();
            } else {
                stack.push_back(ch);
            }
        }
        return (stack.empty());
    }
};
