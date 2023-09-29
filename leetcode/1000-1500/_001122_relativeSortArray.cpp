class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> ranking;
        for (int i=0; i<arr2.size(); i++) {ranking[arr2[i]] = i;}
        vector<int> ans = arr1;
        std::sort(ans.begin(), ans.end(), [&ranking](int left, int right) -> bool {
            auto lit = ranking.find(left);
            auto rit = ranking.find(right);
            if (lit == ranking.end() && rit == ranking.end()) {
                return left < right;
            }
            if (lit == ranking.end()) {
                return false;
            }
            if (rit == ranking.end()) {
                return true;
            }
            return ranking[left] < ranking[right];
        });
        return ans;
    }
};
