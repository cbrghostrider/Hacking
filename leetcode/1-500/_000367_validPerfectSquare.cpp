class Solution {
public:
    // returns the closest number x that we can guess, such that:
    // x * x <= query_num 
    // x will be used as the starting point for next binary search
    int findNextGuess(int guess, int query_num) {
        if (guess * guess == query_num) {
            return guess;
        }
        
        long long step = 1;
        while ((guess + step) * (guess + step) <= query_num) {
            step *= 2;
        }
        
        return guess + (step/2);
    }

    bool isPerfectSquare(int num) {
        int guess = 1;
        
        while (true) {
            int new_guess = findNextGuess(guess, num);
            if (new_guess * new_guess == num) {
                return true;
            } else if (new_guess == guess) {
                return false;
            } 
            guess = new_guess;
        }
        
    }
};
