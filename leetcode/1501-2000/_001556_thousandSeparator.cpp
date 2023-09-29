class Solution {
public:
    string thousandSeparator(int n) {
        if (n == 0) { return "0"; }
        string ans;
        while (n) {
            int rem = n % 1000;
            n = n/1000;
            string num = std::to_string(rem);
            string sep;
            if (n) { 
                sep = "."; 
                if (num.size() != 3) {num = std::string(3-num.size(), '0') + num;}
            }
            ans = sep + num + ans;
        }
        return ans;
    }
};
