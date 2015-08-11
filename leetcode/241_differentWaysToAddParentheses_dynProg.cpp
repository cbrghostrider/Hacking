// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
typedef unordered_map<string, vector<int>> ValCache;

class Solution {
    string operators = "+-*";
    enum Operators {Plus, Minus, Multiply};
    ValCache valCache;

    int parseNumber(string& input, int fromInd, size_t& outpos) {
        bool isNeg = false;
        if (input[0] == '-') isNeg = true;
        outpos = input.find_first_of(operators, (isNeg ? fromInd+1 : fromInd));
        int retval = std::stoi(input.substr(fromInd, outpos));
        return retval;
    }

    int performReduction(int firstval, int secondval, char op) {
        if (op == '+') {
            return (firstval + secondval);
        } else if (op == '-') {
            return (firstval - secondval);
        } else { //multiply
            return (firstval * secondval);
        }
    }
public:
    vector<int> diffWaysToCompute_(string input) {
        auto fit = valCache.find(input);
        if (fit != valCache.end()) return fit->second;

        vector<int> retval;
        size_t fromInd = 0, pos = 0;
        bool singleNumber = true;
        while ((pos = input.find_first_of(operators, fromInd)) != string::npos) {
            singleNumber = false;
            vector<int> evalOps1 = diffWaysToCompute_(input.substr(0, pos));
            vector<int> evalOps2 = diffWaysToCompute_(input.substr(pos+1));
            char op = input[pos];
            for (int& v1 : evalOps1) {
                for (int& v2 : evalOps2) {
                    retval.push_back(performReduction(v1, v2, op));
                }
            }
            fromInd = pos+1;
            if (input[fromInd] == '-') fromInd++; //skip leading minus signs on numbers
        }
        if (singleNumber) {
            retval.push_back(parseNumber(input, 0, pos));
        }

        valCache.insert(make_pair(input, retval));
        return retval;
    }
    vector<int> diffWaysToCompute(string& input) {
        if (input.length() == 0) return vector<int>();
        return (diffWaysToCompute_(input));
    }
};
