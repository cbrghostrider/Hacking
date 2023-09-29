class Solution {
    // Adds two positive integers a, b
    uint32_t add(uint32_t a, uint32_t b) {
        uint32_t carry = 0;
        uint32_t mask = 0x1;
        uint32_t result = 0;
        for (int i=0; i<32; i++) {
            int bit_a = (mask & a ? 1 : 0);
            int bit_b = (mask & b ? 1 : 0);
            int add_all = carry + bit_a + bit_b;
            if (add_all == 0) {
                carry = 0;
            } else if (add_all == 1) {
                result |= mask;
                carry = 0;
            } else if (add_all == 2) {
                carry = 1;
            } else {
                result |= mask;
                carry = 1;
            }
            mask <<= 1;
        }
        if (carry) {
            result |= mask;
        }
        return result;
    }
    
    // Subs two positive integers a, b, also a >= b.
    uint32_t sub(uint32_t a, uint32_t b) {
        uint32_t borrow = 0;
        uint32_t mask = 0x1;
        uint32_t result = 0;
        for (int i=0; i<32; i++) {
            int bit_a = (mask & a ? 1 : 0);
            int bit_b = (mask & b ? 1 : 0);
            int borrow_p_b = borrow + bit_b;
            if (borrow_p_b == 0 && bit_a == 0) {
                borrow=0;
            } else if (borrow_p_b == 0 && bit_a == 1) {
                result |= mask;
                borrow = 0;
            } else if (borrow_p_b == 1 && bit_a == 0) {
                result |= mask;
                borrow = 1;
            } else if (borrow_p_b == 1 && bit_a == 1) {
                borrow = 0;
            } else if (borrow_p_b == 2 && bit_a == 0) {
                borrow = 1;
            } else {
                borrow = 1;
                result |= mask;
            }
            mask <<= 1;
        }
        // borrow should always be 0 here because we have a>b.
        return result;
    }
    
public:
    int getSum(int a, int b) {
        if (a >= 0 && b >= 0) return add(a, b);
        if (a < 0 && b >= 0) {
            int aprime = -1*a;
            if (aprime == b) return 0;
            if (aprime > b) {int s = sub(aprime, b); return -1 * s;}
            if (aprime < b) {return sub(b, aprime);}
        }
        if (a >= 0 && b < 0) {
            int bprime = -1*b;
            if (a == bprime) return 0;
            if (bprime > a) {int s = sub(bprime, a); return -1 * s;}
            if (bprime < a) {return sub(a, bprime);}
        }
        // a < 0, b < 0
        int aprime = -1*a, bprime = -1*b;
        return -1 * add(aprime, bprime);
    }
};
