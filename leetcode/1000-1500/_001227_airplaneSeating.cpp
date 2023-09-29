class Solution {
public:    
    double nthPersonGetsNthSeat(int n) {
        if (n == 1) return 1;
        
        // let probs[i] be the probability that the last person picked the correct seat (for i people)
        vector<double> probs(n+1, 0.0);
        probs[1] = 1;
        probs[2] = 0.5;
        for (int i=3; i<=n; i++) {      
            // we have i seats, exactly one of which is wrongly occupied, 
            // and thus one position that is unassigned (should have been occupied earlier)
            // 
            // for the last person to occupy the right seat, we have the following:
            // 1. The first person's seat is wrongly occupied, they pick another seat at random, 
            //    which does NOT happen to be the unassigned one.
            // 2. The first person's seat is wrongly occupied, they pick another seat at random, 
            //    which DOES happen to be the unassigned one.
            // 3. The first person's seat is NOT wrongly occupied, so they pick that one.
            // In each case, we get a smaller subproblem.
            double c1 = (1.0/i) * (((double)(i-1))/i) * probs[i-1];
            double c2 = (1.0/i) * (1.0/i) * probs[i-1];
            double c3 = (((double)(i-1))/i) * probs[i-1];
            probs[i] = c1 + c2 + c3;
            // If you look carefully, the numerators/denominators cancel out after the sum.
            // so future probs[i] are always just 0.5
        }
        return probs[n];
    }
};
