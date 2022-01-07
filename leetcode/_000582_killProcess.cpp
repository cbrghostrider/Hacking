class Solution {
    unordered_map<int, vector<int>> children;
    
    vector<int> allChildren(int pid) {
        vector<int> ans;
        for (int child : children[pid]) {
            vector<int> cans = allChildren(child);
            ans.insert(ans.end(), cans.begin(), cans.end());
            ans.push_back(child);
        }
        return ans;
    }
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        
        for (int i=0; i<ppid.size(); i++) {
            children[ppid[i]].push_back(pid[i]);
        }
        
        vector<int> ans = allChildren(kill);
        ans.push_back(kill);
        return ans;
    }
};
