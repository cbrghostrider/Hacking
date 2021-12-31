// 
// Not the prettiest soln... UGH!
//
class Solution {
    // Info records information about the shortest path from
    // target (n-1) to node "node".
    struct Info {
        int node=-1;    // from target (n-1) to "node"
        long len=std::numeric_limits<int>::max();  // len of shortest path
        int num_ways=-1;  // num ways to get there
        // vector<int> prev_nodes; // prev_nodes to get here via shortest path (may be more than 1)
    };
    
    // heap elem used by the min_heap
    struct HElem {
        int node=-1; // which node is it for
        int ver=-1;  // what version does it correspond to (used to skip invalid heap elems)
        long dist=0; // dist to get here from tgt
        int prev_node=-1;  // which node did I get here from
    };
    // stores info for adjacency list
    struct GElem {        
        int node=0;  // connected to node
        int edge=0;  // edge weight
    };
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        unordered_map<int, vector<GElem>> graph;
        for (const auto& road : roads) {
            graph[road[0]].push_back({road[1], road[2]});
            graph[road[1]].push_back({road[0], road[2]});
        }
        
        // shortest path from target (n-1) to node "key"
        // (Key, value)
        unordered_map<int, Info> infos;      // DONE, shortest path found to this node.
        unordered_map<int, long> infos_ip;    // in progress, not yet found (node->dist)
        unordered_map<int, int> counts_ip;   // counts in progress
        vector<int> versions(n, 0);  // used for versioning nodes on the heap
        
        auto comp = [](const HElem& lhs, const HElem& rhs) -> bool {
            if (lhs.dist != rhs.dist) return lhs.dist > rhs.dist;
            return lhs.ver > rhs.ver;
        };
        
        // (node, dist)
        priority_queue<HElem, vector<HElem>, decltype(comp)> min_heap(comp);
        min_heap.push({n-1, versions[n-1], 0, -1});
        infos_ip.insert({n-1, 0});
        counts_ip[n-1] = 1;
        
        while (!min_heap.empty()) {
            auto elem=min_heap.top(); min_heap.pop();
            if (elem.ver < versions[elem.node]) {continue;}  // outdated heap elem
                        
            Info info = {elem.node, elem.dist, elem.node == -1 ? 1 : /*infos[elem.prev_node].num_ways*/
                                              counts_ip[elem.node]};
            if (infos.find(elem.node) != infos.end() && infos[elem.node].len < elem.dist) {
                continue;  // This is not shortest path to node
            }
            
            // Found a shortest path to a node in graph.
            infos[elem.node] = info;            
            infos_ip.erase(elem.node);
            
            for (GElem gelem : graph[elem.node]) {
                if (gelem.node == elem.prev_node) continue;
                long new_dist = elem.dist + gelem.edge;
                if (infos_ip.find(gelem.node) == infos_ip.end() || infos_ip[gelem.node] > new_dist) {
                    min_heap.push({gelem.node, ++versions[gelem.node], new_dist, elem.node});
                    infos_ip[gelem.node] = new_dist;
                    counts_ip[gelem.node] = elem.node == -1 ? 1 : counts_ip[elem.node];
                } else if (infos_ip[gelem.node] == new_dist) {
                    counts_ip[gelem.node] += counts_ip[elem.node];
                    counts_ip[gelem.node] %= 1000000007;
                }                
            }            
        }
        return infos[0].num_ways;
    }
};
