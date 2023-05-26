class Solution {
    map<int, set<int>> adjlist;
    struct Info {
        long long repr=1;
        int visits=0;
        bool done = false;  // picked as source
    };
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        if (roads.empty()) return 0;
        for (const vector<int>& road : roads) {
            adjlist[road[0]].insert(road[1]);
            adjlist[road[1]].insert(road[0]);
        }

        vector<Info> source_info(adjlist.size(), Info());

        // The initial sources.
        vector<int> sources;
        for (const auto& kv : adjlist) {
            if (kv.second.size() == 1) {
                if (kv.first == 0) continue;
                sources.push_back(kv.first);
                source_info[kv.first].done = true;
            }
        }
        
        long long liters = 0;
        while (1) {
            if (sources.size() == 1 && sources[0] == 0) {                
                break;  // Reached the capital city.
            }            
            set<int> touched;  // cities touched by existing sources
            vector<int> ready;  // some of the touched become ready as new sources            
            
            while (!sources.empty()) {
                int src = sources.back();
                sources.pop_back();
                for (int city : adjlist[src]) {
                    if (source_info[city].done) continue;
                    // Found outgoing edge towards capital.
                    long long repr = source_info[src].repr;
                    long long my_liters = (repr/seats) + (repr % seats ? 1 : 0);
                    liters += my_liters;
                    source_info[city].repr += source_info[src].repr;                    
                    source_info[city].visits++;
                    touched.insert(city);
                }
            }
            
            for (int touch : touched) {
                if (touch != 0 && source_info[touch].visits == adjlist[touch].size()-1 || 
                    touch == 0 && source_info[touch].visits == adjlist[touch].size()) { 
                    ready.push_back(touch);
                    source_info[touch].done = true;
                }
            }
            sources = ready;
        }
        return liters;
    }
};
