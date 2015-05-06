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
