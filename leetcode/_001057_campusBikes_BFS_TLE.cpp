//
// Note that this solution is useful if there are obstacles and shit.
// So that we have to actually navigate around things.
// As it stands right now, we don't need all the complexity of BFS.
//
// Currently the complexity is O(m*X*Y), which can become very large.
//
class Solution {
    // Stores information about worker traversal during BFS.
    struct Info {
        int x=0;
        int y=0;
        int index=0;
        int dist=0;
    };
    const int MAX=1000; // limits for x, y
    
    using PairHash = std::function<size_t(const pair<int, int>&)>;
    using BikeMap = unordered_map<pair<int, int>, int, PairHash>;
    
    // maps coord of bike -> bike#
    BikeMap bikemap;
    
    unordered_set<string> visited;
    
    string sig(int w, int x, int y) {
        return std::to_string(w) + "-" + std::to_string(x) + "-" + std::to_string(y);
    }
    
    bool isVisited(int worker, int x, int y) {
        return (visited.find(sig(worker, x, y)) != visited.end());
    }
    
    void visit(int worker, int x, int y) {
        visited.insert(sig(worker, x, y));
    }
    
public:
    // Put all the workers in a queue, IN ORDER of smallest to largest worker index.
    // Then we perform a BFS collectively.
    // When a worker lands on a coordinate that has a bike, it is assigned and it exits the queue.
    // Else we continue BFS for that worker
    // We stop when all the workers are assigned.
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        PairHash pairHash = [](const pair<int, int>& v) -> size_t {return ((v.first << 16) | v.second);};
        bikemap = BikeMap(100/*=bucket_count*/, pairHash);
        
        for (int i=0; i<bikes.size(); i++) {
            bikemap[make_pair(bikes[i][0], bikes[i][1])] = i;
        }
        
        std::queue<Info> q;
        for (int i=0; i<workers.size(); i++) {
            int x=workers[i][0];
            int y=workers[i][1];
            q.push({x, y, i, 0/*=dist*/});
            visit(i, x, y);
        }
        
        vector<int> ans(workers.size(), -1);
        int unassigned=workers.size();
        
        while (!q.empty()) {
            Info info = q.front(); q.pop();
            if (ans[info.index] != -1) continue;  // already found a bike
            
            pair<int, int> coord = make_pair(info.x, info.y);
            if (bikemap.find(coord) != bikemap.end()) {
                // Found an unassigned bike, take it!
                ans[info.index] = bikemap[coord];
                bikemap.erase(coord);
                unassigned--;
                if (unassigned == 0) { break; }
            }
            
            int x=info.x;
            int y=info.y;
            if (info.x != 0 && !isVisited(info.index, x-1, y)) {
                visit(info.index, x-1, y);
                q.push({x-1, y, info.index, info.dist+1});
            }
            if (info.x != MAX-1 && !isVisited(info.index, x+1, y)) {
                visit(info.index, x+1, y);
                q.push({x+1, y, info.index, info.dist+1});
            }
            if (info.y != 0 && !isVisited(info.index, x, y-1)) {
                visit(info.index, x, y-1);
                q.push({x, y-1, info.index, info.dist+1});
            }
            if (info.y != MAX-1 && !isVisited(info.index, x, y+1)) {
                visit(info.index, x, y+1);
                q.push({x, y+1, info.index, info.dist+1});
            }
        }
        return ans;
    }
};
