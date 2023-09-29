// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    vector<unordered_set<int> > edgeListFromTo_; //edge from index to every node in list (where exists)
    vector<unordered_set<int> > edgeListToFrom_; //edge to index from every node in list (where exists)
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> sources, sinks;
        for (int i=0; i<numCourses; i++) {
            edgeListFromTo_.push_back(unordered_set<int>());
            edgeListToFrom_.push_back(unordered_set<int>());
        }
        
        for (vector<int>& deps : prerequisites) {
            if (deps.size() == 0) continue;
            sinks.push_back(deps[0]);
            for (int i=1; i<deps.size(); i++) {
                edgeListFromTo_[deps[i]].insert(deps[0]); //edge from deps[i] to deps[0]
                edgeListToFrom_[deps[0]].insert(deps[i]); //edge to deps[0] from deps[i] 
                sources.push_back(deps[i]);
            }
        }
        
        if (sources.empty() || sinks.empty()) return true; //no dependencies 
        
        sort(sources.begin(), sources.end());
        auto srceit = unique(sources.begin(), sources.end());
        sort(sinks.begin(), sinks.end());
        auto snkeit = unique(sinks.begin(), sinks.end());
        
        vector<int> graphSources;
        set_difference(sources.begin(), srceit, sinks.begin(), snkeit, back_inserter(graphSources));
        if (graphSources.empty()) return false;
        
        //topological sort (Kahn's algorithm)
        vector<int> subset = graphSources;
        while (!subset.empty()) {
            int node = subset.back(); subset.pop_back();
            for (const int& towards : edgeListFromTo_[node]) {
                edgeListToFrom_[towards].erase(node);
                if (edgeListToFrom_[towards].empty()) {
                    subset.push_back(towards);
                }
            }
            edgeListFromTo_[node].clear();
        }
        
        for (unordered_set<int>& bag : edgeListToFrom_) {
            if (!bag.empty()) return false;
        }
        return true;
    }
};
