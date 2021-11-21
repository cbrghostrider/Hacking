class Solution {
public:
    string largestOddNumber(string num) {
        int i=num.size()-1;
        for (; i>=0; i--) {
            int dig = std::stoi(std::string(1, num[i]));
            if (dig % 2 != 0) {
                break;
            }
        }
        return num.substr(0, i+1);
    }
};
