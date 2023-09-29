/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessBounded(int lower, int higher) {
        if (lower == higher) {
            return lower;
        } else if (lower + 1 == higher) {
            if (guess(lower) == 0) {
                return lower;
            }
            return higher;
        }
        
        int mid = ((long long)lower + higher) / 2;
        int guess_result = guess(mid);
        if (guess_result == 0) {
            return mid;
        } else if (guess_result == -1) {
            return guessBounded(lower, mid);   
        }
        return guessBounded(mid, higher);
    }
    
    int guessNumber(int n) {
        return guessBounded(1, n);
    }
};
