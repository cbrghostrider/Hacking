class Solution {
    // Adds a minute.
    void inc(string& time) {        
        if (time[4] >= '0' && time[4] <= '8') {
            time[4]++;
        } else if (time[3] >= '0' && time[3] <= '4') {
            time[3]++;
            time[4] = '0';
        } else if (time.substr(0, 2) == "23") {
            time = "00:00";
        } else {
            time = to_string(stoi(time.substr(0, 2)) + 1) + ":00";
            if (time.size() == 4) {time = "0" + time;}
        }
    }
    
    // Subtracts a minute.
    void dec(string& time) {
        if (time[4] >= '1' && time[4] <= '9') {
            time[4]--;
        } else if (time[3] >= '1' && time[3] <= '5') {
            time[3]--;
            time[4] = '9';
        } else if (time.substr(0, 2) == "00") {
            time = "23:59";
        } else {
            time = to_string(stoi(time.substr(0, 2)) - 1) + ":00";
            if (time.size() == 4) {time = "0" + time;}
        }
    }
    
    bool isValid(const string& str, const unordered_set<char>& check) {
        for (char ch : str) {
            if (check.find(ch) == check.end()) return false;
        }
        return true;
    }
public:
    //
    // Initially I had assumed that "closest time" would mean finding
    // either the time closest later, or closest earlier, and returning the
    // smaller difference.
    // 
    // Of course, the problem only wants the "next" closest time, so now I just
    // return that instead.
    // I left in the other stuff because it is interesting.
    //
    string nextClosestTime(string time) {
        unordered_set<char> comps;
        for (char ch : time) {
            comps.insert(ch);
        }
        if (comps.size() == 2) return time;
        
        string up=time, down=time;
        int count_up=0, count_down=0;
        
        while (1) {
            count_up++;
            inc(up);
            if (isValid(up, comps)) {break;}
        }
        while (1) {
            count_down++;
            dec(down);
            if (isValid(down, comps)) {break;}
        }
        return up;
    }
};
