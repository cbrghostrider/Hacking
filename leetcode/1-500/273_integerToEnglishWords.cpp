// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    vector<string> numbers20 = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", 
                                "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen", "Twenty"};
    vector<string> tens      = {"Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> powers10  = {"", "Thousand", "Million", "Billion"} ;
    
    //num here will be 0 < num < 1000
    string convert(int num, int iteration) {
        string retval;
        int q100 = num / 100;
        if (q100) retval += " " + numbers20[q100 - 1] + " Hundred";
        num = num % 100;
        if (num && num <= 20) {
            retval += " " + numbers20[num-1];
        } else {
            int q10  = num / 10;
            if (q10) retval += " " + tens[q10-1];
            num = num % 10;
            if (num) retval += " " + numbers20[num-1];
        }
        if (iteration) retval += " " + powers10[iteration];
        return retval;
    }
public:
    string numberToWords(int num) {
        if (num <=0 ) return "Zero";
        
        string retval;
        int iteration = 3;
        while (num) {
            int pow10 = pow(1000, iteration);
            int numr3 = num % pow10;
            int numq3 = num / pow10;
            if (numq3) retval = retval + convert(numq3, iteration);
            iteration--;
            num = numr3;
        }
        if (retval[0] == ' ') retval = retval.substr(1);
        return retval;
    }
};
