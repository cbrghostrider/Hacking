class RandomizedSet {
    vector<int> container;  // stores actual values; only grows
    unordered_map<int, int> val_to_ind;  // values that actually exist, mapped to their index in container
    
public:
    RandomizedSet() {}
    
    bool insert(int val) {
        if (val_to_ind.find(val) != val_to_ind.end()) return false;
        container.push_back(val);
        val_to_ind[val] = container.size() - 1;
        return true;
    }
    
    bool remove(int val) {
        if (val_to_ind.find(val) == val_to_ind.end()) return false;
        int ind = val_to_ind[val];
        int swapping = container[container.size()-1];
        std::swap(container[ind], container[container.size()-1]);
        container.pop_back();
        val_to_ind[swapping] = ind;
        val_to_ind.erase(val);
        return true;
    }
    
    int getRandom() {
        return (container[std::rand() % container.size()]);
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
