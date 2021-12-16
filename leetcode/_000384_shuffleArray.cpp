class Solution {
    const vector<int> vals;
public:
    Solution(vector<int>& nums) :vals(nums) {}
    
    vector<int> reset() {
        return vals;
    }
    
    vector<int> shuffle() {
        vector<int> shuffled = vals;
        int count=vals.size();
        
        for (int i=0; i<vals.size(); i++) {
            int r = std::rand()%count;
            std::swap(shuffled[i], shuffled[i+r]);
            count--;
        }
        return shuffled;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
