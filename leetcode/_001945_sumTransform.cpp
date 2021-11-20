class Solution {
public:
    int getLucky(string s, int k) {
        string num_s;
        for (char ch : s) {num_s += std::to_string(ch-'a'+1);}
        auto xfm = [](const string& in) -> string {
            int sum=0;
            for (char ch : in) {sum += std::stoi(std::string(1, ch));}
            return std::to_string(sum);
        };
        for (int i=0; i<k; i++) {num_s = xfm(num_s);}
        return std::stoi(num_s);
    }
};
