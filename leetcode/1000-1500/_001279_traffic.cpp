class TrafficLight {
    const bool RED=false;
    const bool GREEN=true;
    const int NS=1;
    const int EW=2;
    vector<bool> light_status;
    std::mutex traffic;
public:
    TrafficLight() {
        light_status = vector<bool>(3, RED);
        light_status[1] = GREEN;
    }

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        traffic.lock();
        if (roadId == NS && light_status[NS] != GREEN) {
            turnGreen();
            light_status[NS] = GREEN;
            light_status[EW] = RED;
        }
        if (roadId == EW && light_status[EW] != GREEN) {
            turnGreen();
            light_status[EW] = GREEN;
            light_status[NS] = RED;
        }
        crossCar();
        traffic.unlock();
    }
};
