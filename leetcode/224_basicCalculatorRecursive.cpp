// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

// This solution currently gives memory limit exceeded
// Presumably because some degenerate input case is leading to too much recursion
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include <assert.h>

using std::pair;
using std::make_pair;
using std::string;
using std::vector;

class Solution {
    // expr = NUMBER | '(' expr ')' | expr '+' expr | expr '-' expr
    
    enum Operator {PLUS, MINUS};
    
    string eatWhiteSpaces(string s) {
        string ret;
        for (int i=0; i<s.size(); i++) {if (s[i] != ' ') ret.push_back(s[i]);}
        return ret;
    }
    
    pair<int, string> evalExprNumber(string str, bool isneg) {
        auto pos = str.find_first_of("+-()");
        string nstr = str.substr(0, pos);
        string rest = pos == string::npos ? "" : str.substr(pos);
        int mult = isneg ? -1 : 1;
        return make_pair(stoi(nstr) * mult, rest);
    }
    
    pair<int, string> evalExprBrackets(string s, bool isneg) {
        assert(s[0] == '(');
        pair<int, string> vsp = expr(s.substr(1), false);
        string retstr = vsp.second.substr(1); //drop trailing ')'
        int mult = isneg ? -1 : 1;
        return make_pair(vsp.first * mult, retstr);
    }
    
    pair<int, string> eval(string s, bool isneg) {
        if (s[0] == '(') {
            return evalExprBrackets(s, isneg);
        } else {
            return evalExprNumber(s, isneg);
        }
    }
    
    //computes this string
    pair<int, string> expr(string s, bool isneg) {
        if (s.length() == 0) return make_pair(0, "");
        pair<int, string> vsp = eval(s, isneg);
        
        string& rest = vsp.second;
        if (rest.empty() || rest[0] == ')') {
            return vsp;
        }
        
        bool passneg = rest[0] == '-';
        rest = rest.substr(1);
        pair<int, string> rvsp = expr(rest, passneg);
        
        return make_pair(vsp.first + rvsp.first, rvsp.second);
    }
    
public:
    int calculate(string s) {
        s = eatWhiteSpaces(s);
        auto compute = expr(s, false);
        return compute.first;
    }
};
