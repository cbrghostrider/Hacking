class Solution {
    std::priority_queue<int, vector<int>, std::less<int>> cookies;
    std::priority_queue<int, vector<int>, std::less<int>> greed;
    int num_children = 0;
    int num_discontents = 0;
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        num_children = g.size();
        for (int gr : g) {greed.push(gr);}
        for (int sz : s) {cookies.push(sz);}
        while (!greed.empty()) {
            int curr_greed = greed.top();
            greed.pop();
            
            if (cookies.empty() || curr_greed > cookies.top()) {
                num_discontents++;
                continue;
            } 
            
            cookies.pop();
        }
        return (num_children - num_discontents);
    }
};
