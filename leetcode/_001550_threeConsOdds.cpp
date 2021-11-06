class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        if (arr.size() < 3) return false;
        int odds = (arr[0]%2) + (arr[1]%2) + (arr[2]%2);
        if (odds == 3) return true;
        
        for (int i=3; i<arr.size(); i++) {
            if (arr[i-3]%2) odds--;
            if (arr[i]%2) odds++;
            if (odds == 3) return true;
        }
        return false;
    }
};
