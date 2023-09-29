class Solution {
    unordered_map<int, unordered_set<int>> out_edges, in_edges;
    set<int> has_out, has_in, exists;
    vector<int> sources, dests;
    int N;
    
    void prework(vector<vector<int>>& relations) {
        for (int i=0; i<relations.size(); i++) {
            has_out.insert(relations[i][0]);
            has_in.insert(relations[i][1]);
            exists.insert(relations[i][0]);
            exists.insert(relations[i][1]);
            out_edges[relations[i][0]].insert(relations[i][1]);
            in_edges[relations[i][1]].insert(relations[i][0]);
        }
        std::set_difference(exists.begin(), exists.end(), has_out.begin(), has_out.end(), 
                            std::back_inserter(dests));
        std::set_difference(exists.begin(), exists.end(), has_in.begin(), has_in.end(), 
                            std::back_inserter(sources));
    }
    
    unordered_map<int, int> cache;
    
    // computes recursively the #semesters to complete this course
    // caches results for speeding up repeated calls
    // returns -1 if it detects a cycle in dependencies
    int semestersToComplete(int course) {
        if (cache.find(course) != cache.end()) { 
            return cache[course];  // may return -1, if cycle
        }
        if (in_edges.find(course) == in_edges.end()) {  // a pure source
            cache[course] = 1;
            return 1;
        }
        cache[course] = -1;  // mark for possible cycle, will rewrite before end if not
        int semesters=0;
        
        for (int from : in_edges[course]) {
            int mine = semestersToComplete(from);
            if (mine == -1) {semesters = -2; break; }
            if (mine > semesters) {semesters = mine;}
        }
        
        cache[course] = 1 + semesters;
        return cache[course];
    }
    
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        N=n;
        prework(relations);
        if (sources.empty() || dests.empty()) return -1;
        
        int max=0;
        for (int i=0; i<dests.size(); i++) {
            int s = semestersToComplete(dests[i]);
            if (s == -1) return -1;
            if (s > max) {max = s;}
        }
        return max;
        
    }
};
