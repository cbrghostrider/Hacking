class Solution {
public:
    string toHex(int n) {
        if (n == 0) return "0";
        
        uint32_t num = (uint32_t)n;        
        const char* conv = "0123456789abcdef";
        
        string ret;
        while (num) {
            int rem = num%16;
            num /= 16;
            ret.push_back(conv[rem]);
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
};
