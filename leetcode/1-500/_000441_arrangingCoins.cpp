class Solution {
public:
    // Coins used to fully populate "rows" rows.
    long long coinsUsed(long long rows) {
        return (rows * (rows + 1) / 2);
    }
    
    // guessRows will take an initial guess for rows, and the number of coins we have.
    // It will refine this to a better guess of number of rows.
    // Here rows refers to fully filled rows.
    int guessRows(int guess, int n) {
        if (coinsUsed(guess) == n) {
            return guess;
        }
        
        long long step = 1;
        while (coinsUsed(guess + step) <= n) {
            step *= 2;
        }
        return guess + (step / 2);
    }
    
    int arrangeCoins(int n) {
        int guess = 1;
        while (true) {
            int next_guess = guessRows(guess, n);
            if (next_guess == guess) {
                return guess;
            } 
            guess = next_guess;    
        }
    }
};
