class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<int> indices(position.size(), 0);
        for (int i=0; i<indices.size(); i++) {indices[i] = i;}
        std::sort(indices.begin(), indices.end(), [&position, &speed](int lhs, int rhs) -> bool {
            if (position[lhs] != position[rhs]) return position[lhs] < position[rhs];
            return speed[lhs] > speed[rhs];
        });

        int fleets=0;
        double curr_time=0;
        bool last_merged = false;
        for (int i=indices.size()-1; i>=0; i--) {            
            int pos = position[indices[i]];
            int spd = speed[indices[i]];
            int dist = target - pos;
            double indep_time = (double)dist / (double)spd;

            if (indep_time > curr_time) {
                fleets++;  // This is a new fleet starting.
                curr_time = indep_time;                
            } else {
                ;  // nothing to do, this car merged with the prev fleet at some point               
            }
        }        
        return fleets;
    }
};
