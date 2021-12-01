// Substandard solution using holes....
// Better solution is the next one that does swap.
class RandomizedSet {
    int hole_init = -1; // start of hole list in container (stores index)
    vector<int> container;  // stores actual values; only grows
    unordered_map<int, int> val_to_ind;  // values that actually exist, mapped to their index in container
    int count=0;  // how many values in container are valid
    bool has_minus_one = false;  // whether container contains -1; needed during getRandom because this can be a valid value 
    
public:
    RandomizedSet() {
        container = vector<int>(1000, -1);
    }
    
    bool insert(int val) {
        bool is_present = (val_to_ind.find(val) != val_to_ind.end());
        if (is_present) {return false;}
        
        if (hole_init == -1) {
            container.push_back(val);
            val_to_ind[val] = container.size()-1;
        } else {
            int ind = hole_init;
            hole_init = container[hole_init];
            container[ind] = val;
            val_to_ind[val] = ind;
        }
        
        if (val == -1) { has_minus_one = true; }
        count++;
        return true;
    }
    
    bool remove(int val) {
        bool is_present = (val_to_ind.find(val) != val_to_ind.end());
        if (!is_present) {return false;}
        
        int ind = val_to_ind[val];
        container[ind] = hole_init;
        hole_init = ind;
        val_to_ind.erase(val);
        
        if (val == -1) {has_minus_one = false;}
        count--;
        return true;
    }
    
    int getRandom() {
        // roll for -1 value first if needed
        if (has_minus_one) {
            if (count == 1) return -1;
            
            // 1/count chance that minus one is returned.
            int rd = std::rand();
            rd = rd % count;  // 0 ... (count-1) range
            if (rd == 0) {return -1;}  // treat rolling 0 as choosing -1 equally likely among all outcomes
        }
        
        if (count == 0) return -1; // guaranteed by problem conditions not to happen
        
        // if occupancy is "too low", scan values instead of container
        // here we choose < 5%
        if (count < (container.size() / 20)) {
            int rd = std::rand();
            rd = rd % count;
            int k=0;
            for (const auto& kv : val_to_ind) {
                if (k == rd) return kv.first;
                k++;
            }
        }
        
        // If occupancy is more than 5%, then there is a 99.4% chance to find a random element after 
        // 30 tries of the while loop.
        // 1-(.95)^100 = .994
        int chosen = -1;
        while (chosen == -1 || container[chosen] == -1) {
            int rd = std::rand();
            chosen = rd % container.size();  // chosen index
        }
        return container[chosen];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
