class Solution {
    const int INVALID = std::numeric_limits<int>::max();
    
    unordered_map<int, unordered_set<int>> bus_to_stops;    
    unordered_map<int, unordered_set<int>> stop_to_buses;
    
    // marks visited buses
    unordered_set<int> rode_bus;
    
    // memoization cache
    unordered_map<int, unordered_map<int, int>> cache;
    
    int numBuses(int cur_bus, int final_stop) {
        if (cache[cur_bus].find(final_stop) != cache[cur_bus].end()) {
            return cache[cur_bus][final_stop];
        }
        
        if (stop_to_buses[final_stop].find(cur_bus) != stop_to_buses[final_stop].end()) {return 1;}
        rode_bus.insert(cur_bus);
        
        int least = INVALID;
        for (int stop : bus_to_stops[cur_bus]) {
            for (int other_bus : stop_to_buses[stop]) {
                if (rode_bus.find(other_bus) != rode_bus.end()) continue;
                int my_num = numBuses(other_bus, final_stop);
                if (my_num != INVALID) { least = std::min(least, 1+my_num); }
            }
        }
        
        rode_bus.erase(cur_bus);
        cache[cur_bus][final_stop] = least;
        return least;
    }
    
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        
        // populate
        for (int bus=0; bus<routes.size(); bus++) {
            const vector<int>& route = routes[bus];
            for (int stop : route) {
                bus_to_stops[bus].insert(stop);
                stop_to_buses[stop].insert(bus);
            }
        }
        
        // find
        int least=INVALID;
        for (int bus : stop_to_buses[source]) {
            int my_count = numBuses(bus, target);
            least = std::min(least, my_count);
        }
        return least == INVALID ? -1 : least;
    }
};
