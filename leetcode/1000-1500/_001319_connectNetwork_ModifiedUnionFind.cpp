// 
// This solution uses a modified union-find algorithm.
// It tracks number of connections (cables) in addition to just the sizes and leaders.
// This later helps us determine if we can perform reconnections or not!
//
class Solution {
    vector<int> leaders;
    vector<int> sizes;
    vector<int> cables;
    int N=0;
    
    // returns my leader
    // O(1) time.
    int find(int index) {
        while (leaders[index] != index) {
            index = leaders[index];
        }
        return index;
    }
    
    // unites two groups
    // Note that uniting two groups also adds an additional "cable" between the two groups.
    // O(log n) time.
    void unite(int leader1, int leader2) {
        if (sizes[leader1] < sizes[leader2]) {
            leaders[leader1] = leader2;
            cables[leader2] += cables[leader1] + 1;
            sizes[leader2] += sizes[leader1];
        } else {
            leaders[leader2] = leader1;
            cables[leader1] += cables[leader2] + 1;            
            sizes[leader1] += sizes[leader2];
        }
    }
    
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        N=n;
        leaders = sizes = cables = vector<int>(n, 0);
        for (int i=0; i<N; i++) {
            leaders[i] = i;
            sizes[i] = 1;
        }
        
        for (const vector<int>& conn : connections) {
            int leader1 = find(conn[0]);
            int leader2 = find(conn[1]);
            if (leader1 == leader2) {
                cables[leader1]++;  // an extra cable for my group!
            } else {
                unite(leader1, leader2);
            }
        }
        
        // for individual groups: (sizes, cables)
        // note that an n sized groups needs MINIMUM (n-1) cables
        vector<pair<int, int>> info;
        for (int i=0; i<N; i++) {
            if (leaders[i] != i) continue;
            info.push_back({sizes[i], cables[i]});
        }
        std::sort(info.begin(), info.end(), 
                  [](const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
            int diff_lhs = lhs.second-lhs.first;
            int diff_rhs = rhs.second-rhs.first;
            return (diff_lhs > diff_rhs);
        });
        
        int reconnect=0;
        int excess = info[0].second - (info[0].first - 1);  // n comps, need (n-1) cables
        for (int i=1; i<info.size(); i++) {
            excess += info[i].second - (info[i].first - 1);            
            excess -= 1;  // connect group i with previous groups
            if (excess < 0) return -1;  // not possible
            reconnect++;
        }
        return reconnect;
    }
};
