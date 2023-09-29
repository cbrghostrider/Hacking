class ParkingSystem {
    vector<int> capacity;
    vector<int> occupancy;
    
public:
    ParkingSystem(int big, int medium, int small)  {        
        occupancy = capacity = vector<int>(4, 0);
        capacity[1] = big;
        capacity[2] = medium;
        capacity[3] = small;
    }
    
    bool addCar(int carType) {
        if (occupancy[carType] == capacity[carType]) return false;
        occupancy[carType]++;
        return true;
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
