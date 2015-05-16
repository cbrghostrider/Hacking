class Solution {
private:
    bool illFormedInput(string s) {
        if (s.length() == 0 || s[0] == '0') return true;
        if (s.find("00") != string::npos) return true;
        if (s.find("30") != string::npos) return true;
        if (s.find("40") != string::npos) return true;
        if (s.find("50") != string::npos) return true;
        if (s.find("60") != string::npos) return true;
        if (s.find("70") != string::npos) return true;
        if (s.find("80") != string::npos) return true;
        if (s.find("90") != string::npos) return true;
        return false;
    }
    bool isValid(string num) {
        if (num[0] == '0') return false;
        int number = std::stoi(num);
        return (number >=1 && number <= 26);
    }
public:
    int numDecodings(string s) {
        if (illFormedInput(s)) return 0;
        if (s.length() == 1) return (isValid(s) ? 1 : 0);
        
        //number of ways to construct a decoding from index i to end (dynamic programming cache)
        int cache[s.size()];
        
        //base case
        cache[s.size()-1] = isValid(s.substr(s.size()-1)) ? 1 : 0;
        int numLastTwo    = isValid(s.substr(s.size()-2)) ? 1 : 0;
        cache[s.size()-2] = s[s.size()-2] == '0' ? 0 : cache[s.size()-1] + numLastTwo;
        
        //dynamic programming loop
        for (int ind = s.size()-3; ind >=0; ind--) {
            int numOne = isValid(s.substr(ind, 1)) ? cache[ind+1] : 0;
            int numTwo = isValid(s.substr(ind, 2)) ? cache[ind+2] : 0;
            cache[ind] = numOne + numTwo;
        }
        return cache[0];
    }
};
