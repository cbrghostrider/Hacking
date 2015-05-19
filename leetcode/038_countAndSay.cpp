class Solution {
    string countAndSay(string n) {
        if (n.length() == 0) return "1";
        string result;
        while (n.length()) {
            size_t k = n.find_first_not_of(n[0], 1);
            if (k == string::npos) k = n.length();
            result = result + std::to_string(k) + string(1, n[0]);
            n = n.substr(k);
        }
        return result;
    }
public:
    string countAndSay(int n) {
        string seed = "";
        if (n <= 0) return seed;
        while (n--) {
            seed = countAndSay(seed);
        }
        return seed;
    }
};

