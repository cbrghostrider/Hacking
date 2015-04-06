class Solution {
public:
    
    int charToInt(const char ch) {
        return (ch - '0');
    }
    
    int atoi(string str) {
        if (str == "") {
            return 0;
        }
        
        bool isNeg = false;
        
        for (int i=0; i<str.size(); i++) {
            if (str[i] == ' ') {
                //strip leading whitespace
                continue;
            } else if (str[i] == '-' || str[i] == '+') {
                //strip leading neg or pos sign
                if (i == str.size() - 1) {
                    return 0;
                }
                if (str[i] == '-')
                    isNeg = true;
                    
                str = str.substr(i+1);
                break;
            } else {
                //if I found some other char, break here
                str = str.substr(i);
                break;
            }
        }
        
        for (int i=0; i<str.size(); i++) {
            //break on trailing non-number chars
            if (!(charToInt(str[i]) >=0 && charToInt(str[i]) <= 9)) {
                str = str.substr(0, i);
                break;
            }
        }
        
        long conv=0;
        for(auto it = str.begin(); it != str.end();it++) {
            conv = conv * 10 + charToInt(*it);
            
            if (isNeg && conv > (std::numeric_limits<int>::max() + (long)1)) {
                return std::numeric_limits<int>::min();
            } else if (!isNeg && conv > (long)std::numeric_limits<int>::max()) {
                return std::numeric_limits<int>::max();
            }
        } 

            
        return (isNeg ? (-1)*conv:conv);
    }
};
