// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// This solution does much better with stack space
// and it was accepted by the Online Judge.
//
class Solution {
    // expr = NUMBER | '(' expr ')' | expr '+' expr | expr '-' expr
    enum Operator {PLUS, MINUS};
    void eatWhiteSpaces(string& s) {
        int cp=0;
        for (int rp=0; rp<s.size(); rp++) {
            if (s[rp] != ' ') {
                s[cp++] = s[rp];
            }
        }
        s.erase(cp, string::npos);
    }
    
    //eats up a number and its sign, and returns it
    int evalExprNumber(string& str, int& ind) {
        auto pos = str.find_first_of("+-()", ind);
        int len = pos == string::npos ? str.length() - ind : pos - ind;
        string nstr = str.substr(ind, len);
        ind = pos == string::npos ? str.length() : pos;
        return (stoi(nstr));
    }
    
    int evaluate(string& s, int& pos) {
        int result = 0;
        while (pos < s.length()) {
            if (s[pos] == '(') {
                pos++; //eat open bracket
                result += evaluate(s, pos);
            } else if (s[pos] == ')') {
                pos++; //eat closed bracket
                return result;
            } else if (s[pos] == '+') {
                pos++; //eat plus
                if (s[pos] == '(') {
                    pos++;
                    result += evaluate(s, pos);
                } else {
                    result += evalExprNumber(s, pos);
                }
            } else if (s[pos] == '-') {
                pos++; //eat minus
                if (s[pos] == '(') {
                    pos++;
                    result -= evaluate(s, pos);
                } else {
                    result -= evalExprNumber(s, pos);
                }
            } else { 
                //no leading + or - sign
                result += evalExprNumber(s, pos);
            }
        }
        return result;
    }
    
public:
    int calculate(string s) {
        eatWhiteSpaces(s);
        //return expr(s, false);
        int pos = 0;
        return (evaluate(s, pos));
    }
};
