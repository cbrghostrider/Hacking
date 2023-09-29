class Solution {
public:
    // O(n^2) time, O(n) space. 
    int numTeams(vector<int>& rating) {
        vector<int> lltm(rating.size(), 0);  // index i: left less than me count.
        vector<int> rgtm(rating.size(), 0);  // index i: right greater than me count.
        vector<int> rltm(rating.size(), 0);  // index i: right less than me count.
        vector<int> lgtm(rating.size(), 0);  // index i: left greater than me count.
        
        for (int i=1; i<rating.size(); i++) {
            int l_count=0, g_count=0;
            for (int c=0; c<i; c++) {
                if (rating[c] < rating[i]) {l_count++;}
                if (rating[c] > rating[i]) {g_count++;}
            }
            lltm[i] = l_count;
            lgtm[i] = g_count;
        }
        for (int i=rating.size()-2; i>=0; i--) {
            int l_count=0, g_count=0;
            for (int c=rating.size()-1; c>i; c--) {
                if (rating[c] > rating[i]) {g_count++;}
                if (rating[c] < rating[i]) {l_count++;}
            }
            rgtm[i] = g_count;
            rltm[i] = l_count;
        }    
        
        int count=0;
        // count (rating[i] < rating[j] < rating[k])
        for (int j=1; j<rating.size()-1; j++) {
            count += (lltm[j] * rgtm[j]);
            count += (lgtm[j] * rltm[j]);
        }
        return count;
    }
};
