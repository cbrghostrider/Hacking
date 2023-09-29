class Solution {
public:
    int maximumSwap(int num) {
        vector<int> digits;
        int n=num;
        while (n) {
            digits.push_back(n%10);
            n = n/10;
        }
        if (digits.size() <= 1) return num;
        
        bool swapped=false; 
        int start = digits.size()-1;
        while (!swapped && start >=0) {
            int max_ind=start;
            for (int i=start; i>=0; i--) {
                if (digits[i] >= digits[max_ind]) {max_ind = i;}
            }
            if (max_ind != start && digits[max_ind] != digits[start]) {
                std::swap(digits[start], digits[max_ind]);
                swapped = true;
            } else {
                start--;
            }
        }
        
        int ans=0;
        for (int i=digits.size()-1; i>=0; i--) {
            ans *= 10;
            ans += digits[i];
        }
        return ans;
    }
};
