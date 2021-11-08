class Solution {
    using VPtr = vector<int>*;
public:
    // O(n) time, O(n) space.
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        unordered_map<int, VPtr> starts;
        for (vector<int>& piece : pieces) {starts[piece[0]] = &piece;}
        
        for (int aptr=0; aptr<arr.size();) {
            if (starts.find(arr[aptr]) == starts.end()) return false;
            
            vector<int>& vec = *(starts[arr[aptr]]);
            for (int i=0; i<vec.size(); i++) {
                if (aptr >= arr.size()) return false;
                if (arr[aptr++] != vec[i]) return false;
            }
        }
        return true;
    }
};
