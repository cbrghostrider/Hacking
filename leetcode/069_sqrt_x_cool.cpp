// Here is a small writeup I put on leetcode
// First consider the naive solution: Start checking from n = 1, 2, .... 
// and find the largest n for which n*n <= x. This method will work, but will take 
// O(n) time (or O(sqrt x)). The main problem of course is that we step 1 number ahead at a time.
//
// In order to make this log(n), we have to double our step size at each step. 
// Therefore maintain two guesses (guess, and newguess), with a difference of step between them.
//
// Keep making new guesses (for increasing step sizes) until newguess*newguess > x. 
// Now we know that our answer lies between guess and newguess.
//
// However, at this point our step size is too big, and we need better precision 
// (smaller step size) to check between guess and newguess. The solution to this problem 
// lies of course in recursing again, but starting from guess, and 
// with a step size of 1 (which is again doubled at each step).

class Solution {
    long mySqrt_(long x, long guess) {
        if ((guess*guess) <= x && (((guess+1)*(guess+1)) > x)) return guess;
        long step=1;
        long newguess = guess + step;
        while ((newguess * newguess) <= x) {
            step *= 2;
            guess = newguess;
            newguess = guess + step;
        }
        return mySqrt_(x, guess); //start again with small steps
    }
public:
    int mySqrt(int x) {
        if (x < 0) return -1; //imaginary number
        if (x == 0 || x == 1) return x;
        return mySqrt_(x, 1);
    }
};
