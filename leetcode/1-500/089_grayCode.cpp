// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    unordered_set<int> numbers;     //for constant time lookup of existing numbers
public:
    vector<int> grayCode(int n) {
        vector<int> retval;
        if (n <= 0) { retval.push_back(0); return retval;}
        
        const int size = 0x1 << n;  //I need these many numbers in the sequence
        retval.push_back(0);        //start number
        numbers.insert(0);
        
        //starting from LSB of last number, flip one bit at one time
        //if new number thus formed isn't in the sequence, that is the new number
        //continue till you get all numbers needed
        while (retval.size() != size) {
            int lastNum = retval.back();
            int mask = 0x1;    
            int newNum = lastNum;
            while (numbers.find(newNum) != numbers.end()) {
                newNum = lastNum ^ mask;
                mask <<= 1;
            }
            retval.push_back(newNum);
            numbers.insert(newNum);
        }
        return retval;
    }
};
