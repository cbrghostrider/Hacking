class Solution {
    int N=0;  // the total number of cities
    
    // The following tracks state for cities (index = city).
    vector<int> my_leader;  // the leader for my group
    vector<int> my_size;    // the size of my group (only valid for leaders)
    
    // O(log n) time, since union will switch the pointer of the smaller group.
    int find(int city) {
        while (my_leader[city] != city) {
            city = my_leader[city];
        }
        return city;
    }
    
    // O(1) time.
    void unite(int leader1, int leader2) {
        if (my_size[leader1] > my_size[leader2]) {
            my_leader[leader2] = leader1;
            my_size[leader1] += my_size[leader2];
            return;
        }
        my_leader[leader1] = leader2;
        my_size[leader2] += my_size[leader1];
    }
    
public:
    // O(n*n*logn) time, O(n) space.
    int findCircleNum(vector<vector<int>>& isConnected) {
        N = isConnected.size();
        
        // Initialize.
        for (int i=0; i<N; i++) {
            my_leader.push_back(i);
            my_size.push_back(1);
        }
        
        // Connect.
        for (int i=0; i<isConnected.size(); i++) {
            for (int j=0; j<isConnected.size(); j++) {
                if (isConnected[i][j] == 0) continue;
                if (i == j) continue;
                int leader0 = find(i);
                int leader1 = find(j);
                if (leader0 != leader1) {
                    unite(leader0, leader1);
                }
            }
        }
        
        // Count groups.
        int count=0;
        for (int i=0; i<N; i++) {
            if (my_leader[i] == i) { count++; }
        }
        return count;
    }
};
