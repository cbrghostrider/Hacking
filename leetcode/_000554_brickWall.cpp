class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> crd_counts;
        
        bool blank_wall = true;  // in case there are no boundaries at all!
        for (const vector<int>& row : wall) {
            int sum=0;
            for (int i=0; i<row.size(); i++) {
                sum += row[i];
                if (i != row.size()-1) {
                    blank_wall = false;
                    crd_counts[sum]++;
                }
            }
        }
        
        int max=std::numeric_limits<int>::min(), max_index=-1;
        for (const auto& kv : crd_counts) {
            if (kv.second > max) {
                max = kv.second;
                max_index = kv.first;
            }
        }
        return blank_wall ? wall.size() : wall.size()-max;
    }
};
