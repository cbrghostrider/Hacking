
class Sorter {
private:
    int charToInt(char c) {
        return (c - '0');
    }
public:
    Sorter  () {}
    ~Sorter () {}
    
    bool operator()(const string& lhs, const string& rhs) {
        int plhs = 0, prhs = 0;
        
        //start matching in sequence
        while (plhs < lhs.size() && prhs < rhs.size()) {
            if (charToInt(lhs[plhs]) > charToInt(rhs[prhs])) {
                return true;
            } else if (charToInt(lhs[plhs]) < charToInt(rhs[prhs])) {
                return false;
            } else {
                plhs++; 
                prhs++;
            }
        }
        //everything so far has matched (so lhs is a prefix of rhs or vice-versa)
        
        if (plhs == lhs.size() && prhs == rhs.size()) {
            return false; 
        }
        
        if (plhs == lhs.size()) {
            string subRhs = rhs.substr(prhs);
            Sorter sorter;
            return sorter(lhs, subRhs);
        }
        if (prhs == rhs.size()) {
            string subLhs = lhs.substr(plhs);
            Sorter sorter;
            return sorter(subLhs, rhs);
        }
        return false;
    }
};

class Solution {
private:
    string stripLeadingZeroes(string str) {
        if (str.size() > 1 && str[0] == '0') {
            return stripLeadingZeroes(str.substr(1));
        }
        return str;
    }
    
public:
    string largestNumber(vector<int>& nums) {
        vector<string> numstr;
        numstr.reserve(nums.size());
        
        std::for_each(nums.begin(), nums.end(), [&numstr] (const int& num) -> void {
            numstr.push_back(std::to_string(num));
        });
        
        Sorter sorter;
        std::sort(numstr.begin(), numstr.end(), sorter);

        std::string retval = std::accumulate(numstr.begin(), numstr.end(), string(), [] (const string& lhs, const string& rhs) -> string {
            return (lhs + rhs);
        });
        retval = stripLeadingZeroes(retval);
        return retval;
    }
};

