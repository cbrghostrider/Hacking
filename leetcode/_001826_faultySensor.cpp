class Solution {
    // Compares inclusive.
    bool compareSections(const vector<int>& s1, int s1_begin, int s1_end,
                         const vector<int>& s2, int s2_begin, int s2_end) {
        if ((s1_end-s1_begin+1) != (s2_end-s2_begin+1)) return false;
        int sz = s1_end-s1_begin+1;
        for (int s=0; s<sz; s++) {
            if (s1[s1_begin+s] != s2[s2_begin+s]) return false;
        }
        return true;
    }
    
public:
    int badSensor(vector<int>& sensor1, vector<int>& sensor2) {
        bool early_mismatch = false;  // mismatches before it reaches the last index
        int i=0;
        for (; i<sensor1.size()-1; i++) {
            if (sensor1[i] != sensor2[i]) {
                early_mismatch = true;
                break;
            }
        }
        if (!early_mismatch) {return -1;}
        bool bad_sensor1 = compareSections(sensor1, i, sensor1.size()-2, sensor2, i+1, sensor2.size()-1);
        bool bad_sensor2 = compareSections(sensor1, i+1, sensor1.size()-1, sensor2, i, sensor2.size()-2);
        if (bad_sensor1 == bad_sensor2) return -1;
        if (bad_sensor1) return 1;
        return 2;
    }
};
