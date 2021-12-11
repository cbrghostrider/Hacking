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
    
    // Performs a dfs and finds the longest path to a source from this destination course.
    int dfs(int course) {
        if (cache.find(course) != cache.end()) return cache[course];
        if (in_edges.find(course) == in_edges.end()) {  // a pure source
            cache[course] = 1;
            return 1;
        }
        cache[course] = -1;  // to detect cycle
        int max=1;
        
        // (course, path_len_curr)
        vector<pair<int, int>> stack;
        stack.push_back({course, 1});
        
        while (!stack.empty()) {
            pair<int, int> c_s = stack.back(); stack.pop_back();
            if (c_s.second > max) {max = c_s.second;}
            
            for (int i: in_edges[c_s.first]) {
                if (cache.find(i) != cache.end()) {
                    if (cache[i] == -1) {max = -1; break;}
                    if (max < cache[i]+c_s.second) {max = cache[i] + c_s.second;}
                } else {
                    stack.push_back({i, c_s.second+1});
                }
            }
            
            if (max == -1) {break;}
        }
        
        cache[course] = max;
        return cache[course];
    }
    
public:
   
    // somewhat puzzlingly, the iterative version gets TLE, but not the recursive one
    // though they are essentially very similar...(?) 
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        N=n;
        prework(relations);
        if (sources.empty() || dests.empty()) return -1;
        
        int max=0;
        for (int i=0; i<dests.size(); i++) {
            int s = dfs(dests[i]);
            if (s == -1) return -1;
            if (s > max) {max = s;}
        }
        return max;
    }
};
