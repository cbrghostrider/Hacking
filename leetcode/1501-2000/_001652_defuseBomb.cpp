class Solution {
public:
    // O(n) time, O(1) space.
    vector<int> decrypt(vector<int>& code, int k) {
        vector<int> ans(code.size(), 0);
        if (k == 0) return ans;
        
        if (k > 0) {
            int sum = 0;
            for (int i=0; i<k; i++) sum += code[i];
            int drop = k-1;
            for (int i=code.size()-1; i>=0; i--) {
                ans[i] = sum;
                sum += code[i];
                sum -= code[drop];
                drop = (drop-1+code.size())%(code.size());
            }
        } else {
            k *= -1;
            int sum = 0;
            for (int i=code.size()-k; i<code.size(); i++) sum += code[i];
            int drop = code.size()-k;
            for (int i=0; i<code.size(); i++) {
                ans[i] = sum;
                sum += code[i];
                sum -= code[drop];
                drop = (drop+1)%(code.size());
            }
        }
        return ans;
    }
};
