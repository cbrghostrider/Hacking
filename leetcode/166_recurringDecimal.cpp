class Solution {
    vector<long> digits_;     //digits at positions after decimal point
    vector<long> remainders_; //remainders at positions after decimal point
    
public:
    //return value says whether there is a repeated sequence in the value
    //if yes, then [indexFrom, endofvector] in digits_ gives this sequence
    bool performContinuousDivision(long divisor, long remainder, int& indexFrom) {
        if (remainder == 0) return false; // no continuous sequence
        
        int i=0;
        for (i=0; i<remainders_.size(); i++) {
            if (remainders_[i] == remainder) {
                break; //i is the index from which we will repeat
            }
        }
        if (i != remainders_.size()) { //found repeated sequence
            indexFrom = i;
            return true;
        }
        
        remainders_.push_back(remainder);
        
        long dividend = remainder * 10;
        digits_.push_back(dividend / divisor);
        return performContinuousDivision(divisor, (dividend % divisor), indexFrom);
    }
    
    string fractionToDecimal(int num, int den) {
        string retval;
        if (den == 0) { //division by 0
            return retval;      
        }
        long numerator   = num < 0 ? ((long)num * -1) : num;
        long denominator = den < 0 ? ((long)den * -1) : den;
        long integerPart = numerator / denominator;
        long remainder   = numerator % denominator;
        
        //to record start index of recurring portion
        int from=0;             
        
        bool isRepeat = performContinuousDivision(denominator, remainder, from);
        
        //if integer part is non-zero, or decimal part exists, then add possible sign
        if (integerPart || digits_.size()) { 
            if ((num < 0 && den > 0) || (num > 0 && den < 0)){
                retval += "-";
            }
        }
        
        //add integer part of the number
        retval += std::to_string(integerPart);
        if (remainder == 0) {
            return retval;
        }
        
        //add decimal part of the number
        retval += "."; 
        for (unsigned int i=0; i<digits_.size(); i++) {
            if (isRepeat && i == from) retval += "(";
            retval += std::to_string(digits_[i]);
        }
        if (isRepeat) retval += ")";
        return retval;
    }
};
