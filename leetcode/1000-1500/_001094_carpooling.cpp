class Solution {
public:
    // O(n log n) time, O(n) space.
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // (+/- passengers, index)
        vector<pair<int, int>> route;
        for (int i=0; i<trips.size(); i++) {
            route.push_back(make_pair(trips[i][0], trips[i][1]));
            route.push_back(make_pair(-1*trips[i][0], trips[i][2]));
        }
        std::sort(route.begin(), route.end(), [](const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
            if (lhs.second != rhs.second) return lhs.second < rhs.second;
            return lhs.first < rhs.first;
        });
        int p=0;  // the current number of passengers
        for (int i=0; i<route.size(); i++) {
            p += route[i].first;
            if (p > capacity) return false;
        }
        return true;
    }
};
