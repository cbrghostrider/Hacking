class Solution {
public:
    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        vector<vector<int>> ans;
        int p1=0, p2=0;
        
        while (p1 < encoded1.size() && p2 < encoded2.size()) {
            auto& e1 = encoded1[p1];
            auto& e2 = encoded2[p2];
            int v1=e1[0], v2=e2[0];
            int c1=e1[1], c2=e2[1];
            int new_v=0, new_c=0;
            if (c1 == c2) {
                new_v = v1*v2;
                new_c = c1;
                p1++; p2++;
            } else if (c1 > c2) {
                new_v = v1*v2;
                new_c = c2;
                p2++;
                e1[1] -= c2;
            } else {
                new_v = v1*v2;
                new_c = c1;
                p1++;
                e2[1] -= c1;                
            }
            if (!ans.empty() && ans.back()[0] == new_v) {
                ans.back()[1] += new_c;
            } else {
                ans.push_back({new_v, new_c});
            }
        }
        return ans;
    }
};
