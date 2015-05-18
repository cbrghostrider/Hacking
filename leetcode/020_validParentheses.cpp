class Solution {
    unordered_map<char, char> complement = {{')', '('}, {']', '['}, {'}', '{'}};
public:
    bool isValid(string s) {
        vector<char> stack;
        for (const char& ch : s) {
            if (ch == ')' || ch == ']' || ch == '}') {
                if (stack.empty()) return false;
                if (stack.back() != complement[ch]) return false;
                stack.pop_back();
            } else {
                stack.push_back(ch);
            }
        }
        return (stack.empty());
    }
};
