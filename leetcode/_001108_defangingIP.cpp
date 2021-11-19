class Solution {
public:
    string defangIPaddr(string address) {
        string ret;
        for (char ch : address) {
            if (ch == '.') {
                ret += "[.]";
            } else {
                ret.push_back(ch);
            }
        }
        return ret;
    }
};
