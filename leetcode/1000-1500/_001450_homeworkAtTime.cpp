class Solution {
public:
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
        int discarded = 0;
        for (int i=0; i<startTime.size(); i++) {
            if (startTime[i] > queryTime) discarded++;
            if (endTime[i] < queryTime) discarded++;
        }
        return (startTime.size() - discarded);
    }
};
