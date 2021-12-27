class Solution {
    // At each step, our number of numbers DOUBLES.
    // So if k >= (2^n)/2 at any step, we can just throw away the first half, 
    // and if k < (2^n)/2, we throw away the last half...
public:
    // O(n) time, O(1) space.
    int kthGrammar(int n, int k) {
        int N=n;
        n -= 1;  // convert to 0-indexing for bitwise math
        k -= 1;  // convert to 0-indexing for bitwise math
        int last=0;
        for (int ni=2; ni<=N; ni++) {
            last = (last == 0 ? 1 : 2);  
            int halves = (1 << n) / 2;
            
            if (k < halves) {  // throw away right half
                last &= 0x2;
                last >>= 1;
                // index k is unchanged, but comparison number is halved
                n -= 1;  // comparison number is now halved
            } else {  // throw away left half
                last &= 1;                
                k -= halves;  // index k has now changed
                n -= 1;
            }
        }
        return last;
    }
};
