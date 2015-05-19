class Solution {
public:
    string addBinary(string a, string b) {
        if (a.length() == 0) return b;
        if (b.length() == 0) return a;
        if (a.length() < b.length()) return addBinary(b, a);
        
        b = string(a.length() - b.length(), '0') + b; //add enough leading zeros
        string result(a.length(), '0');
        string carry = "0";
        for (int i=a.length()-1; i >= 0; i--) {
            if (a[i] == '1' && b[i] == '1' && carry == "1") {
                result[i] = '1'; 
                //carry stays the same
            } else if (a[i] == '0' && b[i] == '0' && carry == "0") {
                ;//both result[i] and carry stay the same = 0
            } else if (a[i] == '1' && b[i] == '1') { //1, 1, 0 case
                //result[i] stays the same = 0 
                carry = "1";
            } else if (a[i] == '0' && b[i] == '0') { //0, 0, 1 case
                result[i] = '1';
                carry = "0";
            } else if (carry == "0") { //0, 1, 0 or 1, 0, 0
                result[i] = '1'; //carry stays 0
            } else { //0, 1, 1 or 1, 0, 1
                ;//result[i] stays 0 and carry stays 1
            }
        }
        if (carry == "1") result = carry + result;
        return result;
    }
};
