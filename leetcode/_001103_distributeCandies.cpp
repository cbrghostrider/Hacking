class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> ans(num_people, 0);
        int last = 0;
        while (candies > 0) {
            for (int i=0; i<num_people; i++) {
                last++;
                if (candies <= last) {
                    ans[i] += candies;
                    candies = 0;
                    break;
                }
                ans[i] += last;
                candies -= last;
            }
        }
        return ans;
    }
};
