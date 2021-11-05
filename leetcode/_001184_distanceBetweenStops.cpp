class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        int total = 0;
        for (int i=0; i<distance.size(); i++) total += distance[i];
        
        int first = std::min(start, destination);
        int second = std::max(start, destination);
        int dist = 0;
        for (int i=first; i<second; i++) {
            dist += distance[i];
        }
        return std::min(dist, total - dist);
    }
};
