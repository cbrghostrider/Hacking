class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> result;
        int f_ptr=0, s_ptr=0;
        while (f_ptr < firstList.size() && s_ptr < secondList.size()) {
            vector<int>& f = firstList[f_ptr];
            vector<int>& s = secondList[s_ptr];
            
            if (f[1] < s[0]) {  // first ends entirely before second begins
                f_ptr++;
            } else if (s[1] < f[0]) {  // second ends entirely before first begins
                s_ptr++;
            } else if (f[0] >= s[0] && f[1] <= s[1]) {  // first entirely between second
                result.push_back({f[0], f[1]});
                f_ptr++;
            } else if (s[0] >= f[0] && s[1] <= f[1]) {  // second entirely between first
                result.push_back({s[0], s[1]});
                s_ptr++;
            } else if (f[1] >= s[0] && f[1] <= s[1]) { // first ends between second start and end
                result.push_back({s[0], f[1]});
                f_ptr++;
            } else if (s[1] >= f[0] && s[1] <= f[1]) { // second ends between first start and end
                result.push_back({f[0], s[1]});
                s_ptr++;
            } 
        }
        return result;
    }
};
