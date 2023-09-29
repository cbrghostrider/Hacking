class Solution {
public:
    string generateTheString(int n) {
        if (n <=0) return "";
        if (n % 2 == 0) {
            return (std::string(n-1, 'a') + "b");
        }
        return (std::string(n, 'a'));
    }
};
