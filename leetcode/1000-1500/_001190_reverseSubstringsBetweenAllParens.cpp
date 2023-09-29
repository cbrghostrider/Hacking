class Solution {
    
    // left and right are inclusive
    void reverseBetween(string& s, int left, int right) {
        while (left < right) {
            while (left < right && !isalpha(s[left])) {left++;}
            while (left < right && !isalpha(s[right])) {right--;}
            if (left >= right) break;
            std::swap(s[left], s[right]);
            left++;
            right--;
        }
    }
    
public:
    
    // O(n^2) time, O(n) space for result.
    string reverseParentheses(string s) {
        vector<int> opens;
        for (int i=0; i<s.size(); i++) {
            if (s[i] =='(') {
                opens.push_back(i);
            } else if (s[i] == ')') {
                reverseBetween(s, opens.back(), i);
                opens.pop_back();
            }
        }
        string ret;
        for (char ch : s) {
            if (isalpha(ch)) {ret.push_back(ch);}
        }
        return ret;
    }
};
