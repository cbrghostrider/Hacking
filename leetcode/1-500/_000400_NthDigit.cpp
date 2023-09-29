class Solution {
    int digFromNumber(int num, int dig) {
        string nstr = to_string(num);
        char cdig = ' ';
        if (dig == 0) {
            cdig = nstr.back();
        } else {
            cdig = nstr[dig-1];
        }
        return stoi(string(1, cdig));
    }
    
    int NthDigit(int n, long digits_used, int last_niner, int next_niner, int next_num_digits) {
        long digits_left = n-digits_used;
        int num_of_full_numbers = digits_left/next_num_digits;
        int digit_in_last_num = digits_left % next_num_digits;
        
        int number_to_examine = last_niner + num_of_full_numbers;
        if (digit_in_last_num != 0) {number_to_examine++;}
        
        return digFromNumber(number_to_examine, digit_in_last_num);
    }
    
public:
    // Time: O(log n) to the base 10.
    // Space: O(1).
    int findNthDigit(int n) {
        if (n <= 9) return n;
        
        long digits_used=9;        
        int last_niner=9;
        int last_num_digits=1;
        
        while (1) {
            int next_niner=(last_niner+1)*10 - 1;
            int next_num_digits = last_num_digits+1;
            
            long digits_consumed = (long)(next_niner - last_niner) * next_num_digits;
            long next_digits_used = digits_consumed + digits_used;
            if (next_digits_used < n) {
                digits_used = next_digits_used;
                last_niner = next_niner;
                last_num_digits = next_num_digits;
            } else {
                return NthDigit(n, digits_used, last_niner, next_niner, next_num_digits);
            }
        }
        return -1;  // should not get here
    }
};
