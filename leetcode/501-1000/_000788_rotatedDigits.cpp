class Solution {
    unordered_map<int, int> rotations = {
        {0, 0}, {1, 1}, {8, 8},
        {2, 5}, {5, 2},
        {6, 9}, {9, 6}
    };
    
    // rotations with exceptions
    unordered_map<int, int> rotations_e = {
        {0, 0}, {1, 1}, {8, 8}
    };
    
public:
    // Imagine a number of exactly n significant positions.
    // (A) At each positions, we can choose any of the 7 numbers that can be rotated.
    //
    // (B) However, if a number is ENTIRELY formed only from the 3 numbers that rotate to themselves, 
    //     then that full number is invalid, because its rotation is also fully to itself.
    //
    // (C) Also numbers with leading 0s are invalid, 
    
    // rotatedDigitsNDig number of possible good numbers starting at 1....
    //   having EXACTLY n digits, and no leading zeros
    int rotatedDigitsNDig(int n) {
        if (n == 0) return 0;
        
        // get good numbers from 2 exactly to (n-1) exactly digits
        int upto_nm1 = rotatedDigitsNDig(n-1);
        
        // get good numbers having exactly n digits
        // all_a includes numbers that fall into (A), which includes (B)
        int all_a = 1;
        for (int i=1; i<n; i++) {
            all_a *= 7;
        }
        all_a *= 6;
        
        // get numbers in set (B)
        int all_b=1;
        for (int i=1; i<n; i++) {
            all_b *= 3;
        }
        all_b *= 2; 
        return upto_nm1 + all_a - all_b;
    }
    
    // The above algorithm counts good numbers from 1 to 99999 for example if we gave n=5
    // i.e. it only works on the entire range of n digit numbers (ending at 9999....99999), not some random ending
    // we need to extend it to give us something from 1 to abcde for example, where abcde are random digits (e.g. 1...33453)
    // could break up 33453 into [1..9999] and [10000...33453] and so on...
    // TODO(create algorithm with this additional constraint, using above)
    // That would be O(log n) algorithm (log to base 10).
    
    // O(n) time.
    bool isPossible(int num) {
        vector<int> digs;
        
        int n=num;
        while (n) {
            int dig = n%10;
            if (rotations.find(dig) == rotations.end()) {
                return false;
            }
            digs.push_back(n%10);
            n /= 10;
        }
        for (int& d : digs) {
            d = rotations[d];
        }
        int ret=0;
        for (int i=digs.size()-1; i>=0; i--) {
            ret *= 10;
            ret += digs[i];
        }
        return ret != num;
    }
    
    // Brute force
    int rotatedDigits(int n) {
        int count=0;
        for (int i=1; i<=n; i++) {
            if (isPossible(i)) {count++;}
        }
        return count;
    }
};
