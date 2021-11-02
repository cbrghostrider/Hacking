class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int ptr = 0;
        bool one_bit = false;  // last decoded was one or two bit
        while (ptr < bits.size()) {
            if (bits[ptr] == 0) {
                one_bit = true;
                ptr++;
            } else {
                one_bit = false;
                ptr += 2;
            }
        }
        return one_bit;
    }
};
