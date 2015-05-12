// Solution is algorithmically O(n^1.585) due to divide and conquer, 
// which is better than the naive O(n^2) double for loop
// However, since I am passing all strings by value, and constantly padding zeros, 
// the constants are rather high, also string concat is O(n), 
// which really butchers the algorithmic advantages of D&C (no longer O(n^1.585))!!
// Need to optimize the implementation to fare better.
class Solution {
private:
    int charToInt_(char c) {return (c - '0');}
    
    char prevChar_(char c) {return (c == '0' ? '9' : ('0' + (charToInt_(c) - 1)));}
    
    void padWithZeros_(string& num, int len, bool lhs = true) {
        if (len <= 0) return;
        string zeros(len, '0');
        if (lhs == true) num = zeros + num; else num = num + zeros;
    }
    
    string dropLeadingZeros_(string num) {
        size_t found = num.find_first_not_of("0");
        if (found != std::string::npos) {
            return num.substr(found);
        }
        return "0";
    }
    
    string strAdd_(string lhs, string rhs) {
        assert(lhs.length() == rhs.length());
        char carry = '0';
        string result(lhs.length(), '0');
        for (int i=lhs.length() - 1; i >= 0; i--) {
            string addition = std::to_string(charToInt_(lhs[i]) + charToInt_(rhs[i]) + charToInt_(carry));
            result[i] = addition[addition.length() - 1];
            if (addition.length() > 1) carry = addition[0]; else carry = '0';
        }
        if (carry != '0') result = string(1, carry) + result;
        return result;
    }
    
    string strSub_(string lhs, string rhs) {
        assert(lhs.length() == rhs.length());
        char carry = '0';
        string result(lhs.length(), '0');
        for (int i=lhs.length() - 1; i >= 0; i--) {
            if (carry != '0') {
                lhs[i] = prevChar_(lhs[i]);
                if (lhs[i] == '9') carry = '1'; else carry = '0';
            }
            int lhsdig = charToInt_(lhs[i]);
            int rhsdig = charToInt_(rhs[i]);
            if (lhsdig < rhsdig) {
                lhsdig += 10;
                carry = '1';
            }
            string sub = std::to_string(lhsdig - rhsdig);
            result[i] = sub[0];
        }
        if (carry != '0') assert(0); //by property of the problem
        return result;
    }
    
    //L = x.len/2
    //x = x1*(10^L) +x0; y = y1*(10^L/2) + y0
    //z2 = x1y1, z0 = x0y0, z1 = (x1+x0)*(y1+y0) - z2 -z0
    //xy = z2*(10^2L) + z1*(10^L) + z0
    string karatsubaMultiply_(string x, string y) {
        assert(x.length() == y.length());
        int lenR = x.length() / 2;   //right half
        int lenL = x.length() - lenR;//left half
        
        if (x.length() == 1) {
            string ret = std::to_string(charToInt_(x[0]) * charToInt_(y[0]));
            return ret;
        }
        
        //divide and conquer - get subparts of the big numbers
        string x1 = x.substr(0, lenL);
        string x0 = x.substr(lenL);
        string y1 = y.substr(0, lenL);
        string y0 = y.substr(lenL);
        
        //First 2 terms in karatsuba: z2 = x1y1 and z0 = x0y0
        string z2 = karatsubaMultiply_(x1, y1);
        string z0 = karatsubaMultiply_(x0, y0);
        padWithZeros_(x0, x1.length() - x0.length());
        padWithZeros_(y0, y1.length() - y0.length());
        
        //(x1 + x0) * (y1 + y0) 
        string x10 = strAdd_(x1, x0);
        string y10 = strAdd_(y1, y0);
        padWithZeros_(y10, x10.length() - y10.length());
        padWithZeros_(x10, y10.length() - x10.length());
        string xymult = karatsubaMultiply_(x10, y10);
        
        //Third term in karatsuba: z1 = (x1 + x0) * (y1 + y0) - z2 - z0
        padWithZeros_(z2, xymult.length() - z2.length());
        string interim = strSub_(xymult, z2);
        padWithZeros_(z0, interim.length() - z0.length());
        string z1 = strSub_(interim, z0);
        
        //multiplication is: xy = z2*10^2*LenR + z1*10^lenR + z0
        padWithZeros_(z2, 2*lenR, false);
        padWithZeros_(z1, lenR, false);
        padWithZeros_(z1, z2.length() - z1.length()); 
        string addInterim = strAdd_(z2, z1);
        padWithZeros_(z0, addInterim.length() - z0.length());
        string result = strAdd_(addInterim, z0);
        string ret = dropLeadingZeros_(result);
        return ret;
    }
    
public:

    string multiply(string num1, string num2) {
        int len1 = num1.length();
        int len2 = num2.length();
        if(len1 == 0 || len2 == 0) return "";
        if (len1 > len2) padWithZeros_(num2, len1-len2);
        if (len1 < len2) padWithZeros_(num1, len2-len1);    
        return karatsubaMultiply_(num1, num2);
    }
};
