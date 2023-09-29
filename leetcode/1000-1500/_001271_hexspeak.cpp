class Solution {
    vector<char> to_letter = {'O', 'I', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
public:
    string toHexspeak(string n) {
        string hex;
        int64_t num = std::stoll(n);
        while (num) {
            hex.push_back(to_letter[num%16]);
            num = num/16;
        }
        std::reverse(hex.begin(), hex.end());
        bool valid = (hex.find_first_not_of("ABCDEFIO") == string::npos);
        return (valid ? hex : "ERROR");
    }
};
