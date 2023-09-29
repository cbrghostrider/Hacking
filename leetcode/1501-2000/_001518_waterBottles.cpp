class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int drank=0;
        while (numBottles >= numExchange) {
            int now_drank = (numBottles/numExchange)*numExchange;
            int now_got = numBottles/numExchange;
            int now_leftover = numBottles - now_drank;
            drank += now_drank;
            numBottles = now_got + now_leftover;
        }
        return drank + numBottles;
    }
};
