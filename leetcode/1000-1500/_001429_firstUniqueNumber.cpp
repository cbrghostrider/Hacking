class FirstUnique {
    unordered_map<int, int> counts;
    std::deque<int> deck;
    
    // updates deck state so that its head is the unique number
    void reset() {
        while (!deck.empty() && counts[deck.front()] != 1) {
            deck.pop_front();
        }
    }
public:
    FirstUnique(vector<int>& nums) {
        for (int i=0; i<nums.size(); i++) {
            add(nums[i]);
        }
    }
    
    int showFirstUnique() {
        if (deck.empty()) return -1;
        return deck.front();
    }
    
    void add(int value) {
        deck.push_back(value);
        counts[value]++;
        reset();
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
