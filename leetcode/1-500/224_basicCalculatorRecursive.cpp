// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// currently getting TLE for a really really big input (taking 2.5 seconds)

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include <assert.h>
#include "calc.hpp"

using std::pair;
using std::make_pair;
using std::string;
using std::vector;

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
    
    int evalExprNumber(string& str, bool isneg) {
        auto pos = str.find_first_of("+-()");
        string nstr = str.substr(0, pos);
        str = pos == string::npos ? "" : str.substr(pos);
        int mult = isneg ? -1 : 1;
        return (stoi(nstr) * mult);
    }
    
    int evalExprBrackets(string& s, bool isneg) {
        s = s.substr(1); //drop leading '('
        int val = expr(s, false);
        s = s.substr(1); //drop trailing ')'
        int mult = isneg ? -1 : 1;
        return (val * mult);
    }
    
    int eval(string& s, bool isneg) {
        if (s[0] == '(') {
            return evalExprBrackets(s, isneg);
        } else {
            return evalExprNumber(s, isneg);
        }
    }
    
    //computes this string
    int expr(string& s, bool isneg) {
        if (s.length() == 0) return 0;
        int val = eval(s, isneg);
        
        if (s.empty() || s[0] == ')') {
            return val;
        }
        
        bool passneg = s[0] == '-';
        s = s.substr(1);
        int rval = expr(s, passneg);
        
        return (val + rval);
    }
    
public:
    int calculate(string s) {
        s = eatWhiteSpaces(s);
        return expr(s, false);
    }
};

int main()
{
    string s(EXPRCALC);
    Solution sln;
    int ans = sln.calculate(s);
    std::cout << ans << std::endl;
}
