class Solution {
    unordered_set<int> done;
    
    bool visit(const vector<int>& arr, int index) {
        if (done.find(index) != done.end()) return false;
        done.insert(index);
        
        if (arr[index] == 0) return true;
        
        int back = index-arr[index];
        int front = index+arr[index];
        
        if (back >= 0 && visit(arr, back)) return true;
        if (front <arr.size() && visit(arr, front)) return true;
        
        return false;
    }
    
public:
    // O(n) time to visit every cell.
    // O(n) space in the worst case for recursion.
    bool canReach(vector<int>& arr, int start) {
        return visit(arr, start);        
    }
};
