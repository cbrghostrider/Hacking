class Solution {
    // Starting from root, all the ancestors leading up to and including the child.
    vector<int> ancestors(int child) {        
        vector<int> ans;
        ans.push_back(child);
        while (child != 0) {
            child = (child+1)/2 - 1;            
            ans.push_back(child);            
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
public:
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
        vector<int> ans;
        for (const vector<int>& query : queries) {
            if (query[0] == query[1]) {ans.push_back(1); continue;}
            vector<int> anc0 = ancestors(query[0] - 1);
            vector<int> anc1 = ancestors(query[1] - 1);
            int ind=0;
            int small = std::min(anc0.size(), anc1.size());
            for (; ind < small; ind++) {
                if (anc0[ind] != anc1[ind]) break;              
            }
            int chain = anc0.size() - ind;
            chain += anc1.size() - ind;
            chain++;
            ans.push_back(chain);  
        }
        return ans;
    }
};
