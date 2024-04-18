class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
        int steps=0, water=capacity;
        for (int i=0; i<plants.size(); i++) {
            // Check whether we need to refill
            if (water < plants[i]) {
                steps += i;
                water = capacity;
                steps += i;                
            }
            // Go to the i-th location.
            steps++;            
            // Water the plant.
            if (water < plants[i]) {
                // Impossible: 
                return -1;
            }
            water -= plants[i];
        }
        return steps;
    }
};
