// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totaldiff=0;    //to track if total gas > total cost; if so, circuit possible
        int gasintank=0;
        int start=0;
        for (int i=0; i<gas.size(); i++) {
            int surplus = gas[i] - cost[i];
            totaldiff += surplus;
            gasintank += surplus;
            if (gasintank < 0) { //start point was incorrect, reset
                gasintank=0;
                start = i+1;
            }
        }
        return (totaldiff >=0 ? start: -1);
    }
};
