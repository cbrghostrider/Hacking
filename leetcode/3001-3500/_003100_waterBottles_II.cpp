class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int drunk=0, empty=0;
        while (1) {
            if (numBottles > 0) {                
                drunk += numBottles;
                empty += numBottles;
                numBottles -= numBottles;
            } else if (empty >= numExchange) {                
                empty -= numExchange;
                numBottles++;
                numExchange++;
            } else {
                break;
            }
        }
        return drunk;
    }
};
