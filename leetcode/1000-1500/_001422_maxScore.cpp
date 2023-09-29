class Solution {
public:
    int maxScore(string s) {
        // A string of size n can be broken in (n-1) possible places to give 2 non-empty strings.
        // These vectors store the cumulative sums of lhs zeros or rhs ones, for those strings.
        // O(n) time, O(n) space.
        vector<int> c0sum(s.size()-1, 0), c1sum(s.size()-1, 0);
        int sum = 0;
        for (int i=0; i<s.size()-1; i++) {
            sum += (s[i] == '0' ? 1 : 0);
            c0sum[i] = sum;
        }
        sum = 0;
        for (int i=s.size()-1; i>0; i--) {
            sum += (s[i] == '1' ? 1 : 0);
            c1sum[i-1] = sum;
        }
        int max = std::numeric_limits<int>::min();
        for (int i=0; i<c0sum.size(); i++) {
            int score = c0sum[i] + c1sum[i];
            if (score > max) {max = score;}
        }
        return max;
    }
};
