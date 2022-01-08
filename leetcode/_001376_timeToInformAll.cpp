class Solution {
    unordered_map<int, vector<int>> reports;
    
    int compute(const vector<int>& informTime, int me) {
        if (reports.find(me) == reports.end() || reports[me].size() == 0) {
            return 0;
        }
        int biggest=0;
        for (int r : reports[me]) {
            int time = compute(informTime, r);
            biggest = std::max(time, biggest);
        }
        return informTime[me] + biggest;
    }
public:
    // O(n) time, O(n) space.
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {        
        for (int e=0; e<manager.size(); e++) {
            if (manager[e] == -1) continue;
            reports[manager[e]].push_back(e);
        }
        int time = compute(informTime, headID);
        return time;
    }
};
