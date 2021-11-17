class Solution {
public:
    string addStrings(string num1, string num2) {
        string ans;
        int p1=num1.size()-1, p2=num2.size()-1;
        int carry=0;
        while (p1 >=0 || p2 >=0) {
            int d1 = (p1 >=0 ? std::stoi(std::string(1, num1[p1])) : 0);
            int d2 = (p2 >=0 ? std::stoi(std::string(1, num2[p2])) : 0);
            p1--; p2--;
            int sum = d1 + d2 + carry;
            ans += std::to_string(sum%10);
            carry = sum/10;
        }
        if (carry) { ans += std::to_string(carry);}
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
