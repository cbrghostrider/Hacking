class Solution {
public:
    int bulbSwitch(int n) {
        if (n == 0) return 0;
        
	// Well, this was frustrating...
        // Other than perfect squares, everything else has an even number of divisors 
        // (since the divisors come in pairs)
        
        int count=1;
        int num=2;
        while (num*num <= n) {
            count++;
            num++;
        }
        return count;
    }
};
