class Solution {
public:
    int maximum69Number (int num) {
        std::string nstr = std::to_string(num);
        for (char& ch : nstr) {
            if (ch == '6') {
                ch = '9';
                break;
            }
        }
        return std::stoi(nstr);
    }
};
