class Solution {
    typedef unordered_set<int> Neighbors;
    vector<Neighbors> adjList_;
    
    vector<int> retval_;            // will contain final order of courses to take
    vector<bool> marked_;           // for bookkeeping during dfs
    unordered_set<int> cycDetect_;  // courses on current recursion stack, for cycle detection during dfs 
    
    //return value indicates if successful; unsuccessful if cycle detected!
    bool dfs_(const int node) {
        if (cycDetect_.find(node) != cycDetect_.end()) return false; //cycle!!
        if (marked_[node]) return true; //nothing to do
        marked_[node] = true;
        cycDetect_.insert(node);
        for (const int& neigh : adjList_[node]) {
            if (!dfs_(neigh)) return false;    
        }
        cycDetect_.erase(node);
        retval_.push_back(node);
        return true;
    }

public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        marked_ = vector<bool>(numCourses, false);
        adjList_ = vector<Neighbors>(numCourses, Neighbors());
        
        for (pair<int, int>& rln : prerequisites) adjList_[rln.second].insert(rln.first);
        
        for (int v=0; v<numCourses; v++) {
            if (!marked_[v]) {
                if (!dfs_(v)) return vector<int>(); //cycle!!
            }
        }
        
        std::reverse(retval_.begin(), retval_.end()); //reverse post-order is reversed
        return retval_;
    }
};
