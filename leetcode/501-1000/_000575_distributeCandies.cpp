class Solution {
    std::unordered_set<int> s;
    int distinct = 0;
public:
    int distributeCandies(vector<int>& candyType) {
        for (int c : candyType) {
            if (s.find(c) == s.end()) {
                distinct++;
                s.insert(c);
            }
        }
        return std::min(distinct, (int)(candyType.size()/2));
    }
};
