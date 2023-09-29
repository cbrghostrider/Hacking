class Solution {
    vector<int> leaders;
    vector<int> sizes;
    
    int find(int index) {
        while (leaders[index] != index) {
            index = leaders[index];
        }
        return index;
    }
    
    void unite(int leader1, int leader2) {
        if (leader1 == leader2) return;
        if (sizes[leader1] < sizes[leader2]) {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];
        } else {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];            
        }
    }
    
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        for (int i=0; i<accounts.size(); i++) {
            leaders.push_back(i);
            sizes.push_back(1);
        }
        
        unordered_map<string, int> mail_to_ind;
        for (int i=0; i<accounts.size(); i++) {
            const auto& acct = accounts[i];
            for (int a=1; a<acct.size(); a++) {
                if (mail_to_ind.find(acct[a]) != mail_to_ind.end()) {
                    int leader1 = find(i);
                    int leader2 = find(mail_to_ind[acct[a]]);
                    unite(leader1, leader2);
                } else {
                    mail_to_ind[acct[a]] = i;
                }
            }
        }
        
        unordered_map<int, set<string>> emails;
        map<int, string> names;
        for (int i=0; i<accounts.size(); i++) {
            int leader = find(i);
            names[leader] = accounts[i][0];
            for (int k=1; k<accounts[i].size(); k++) {
                emails[leader].insert(accounts[i][k]);
            }
        }
        
        vector<vector<string>> ans;
        for (const auto& kv : names) {
            int leader = kv.first;
            ans.push_back(vector<string>(1, kv.second));
            for (const auto& email : emails[leader]) {
                ans.back().push_back(email);
            }
        }
        return ans;
    }
};
