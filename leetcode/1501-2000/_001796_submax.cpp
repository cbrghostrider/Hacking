class Solution {
public:
    int secondHighest(string s) {
        int max=-1, submax=-1;
        for (char ch : s) {
            if (!(ch >= '0' && ch <= '9')) continue;
            int n = std::stoi(std::string(1, ch));
            if (n > max) {
                submax = max;
                max = n;
            } else if (n > submax && n != max) {
                submax = n;
            }
        }
        return submax;
    }
};
