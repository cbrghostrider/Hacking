class Solution {

int hash(int curr_x, int curr_y) {
    return ((curr_x << 16) | curr_y);
}
unordered_set<int> htable;

// Returns whether target is reached.
// Won't be called if exploration is in progress for {curr_x, curr_y}.
bool explore(int curr_x, int curr_y, int x, int y, int target) {
    htable.insert(hash(curr_x, curr_y));
    if (curr_x + curr_y == target) return true;

    // Fill x.
    if (curr_x < x) {
        int new_x = x;
        int h = hash(new_x, curr_y);
        if (htable.find(h) == htable.end()) {
            bool poss = explore(new_x, curr_y, x, y, target);
            if (poss) return true;
        }
    }

    // Fill y.
    if (curr_y < y) {
        int new_y = y;
        int h = hash(curr_x, new_y);
        if (htable.find(h) == htable.end()) {
            bool poss = explore(curr_x, new_y, x, y, target);
            if (poss) return true;
        }
    }

    // Empty x.
    if (curr_x != 0) {
        int new_x = 0;
        int h = hash(new_x, curr_y);
        if (htable.find(h) == htable.end()) {
            bool poss = explore(new_x, curr_y, x, y, target);
            if (poss) return true;
        }
    }

    // Empty y.
    if (curr_y != 0) {
        int new_y = y;
        int h = hash(curr_x, new_y);
        if (htable.find(h) == htable.end()) {
            bool poss = explore(curr_x, new_y, x, y, target);
            if (poss) return true;
        }
    }
    
    // From x -> y
    if (curr_x > 0 && curr_y < y) {
        int room_in_y = y - curr_y;
        int water = std::min(curr_x, room_in_y);
        int new_x = curr_x - water;
        int new_y = curr_y + water;
        int h = hash(new_x, new_y);
        if (htable.find(h) == htable.end()) {
            bool poss = explore(new_x, new_y, x, y, target);
            if (poss) return true;
        }        
    }

    // From y -> x 
    if (curr_y > 0 && curr_x < x) {
        int room_in_x = x - curr_x;
        int water = std::min(curr_y, room_in_x);
        int new_x = curr_x + water;
        int new_y = curr_y - water;
        int h = hash(new_x, new_y);
        if (htable.find(h) == htable.end()) {
            bool poss = explore(new_x, new_y, x, y, target);
            if (poss) return true;
        }        
    }

    return false;
}

public:
    bool canMeasureWater(int x, int y, int target) {
        if (x > y) std::swap(x, y);
        if (target > x+y) return false;
        return explore(0, 0, x, y, target);        
    }
};
