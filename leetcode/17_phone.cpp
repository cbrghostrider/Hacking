class Solution {
private:
    std::map<char, string> keyMap_;
    
public:
    Solution() : keyMap_() {
        keyMap_ = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, 
                   {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
    }
    
    vector<string> letterCombinationsPrime(string digits) {
        if (digits.size() == 0) {
            vector<string> retval;
            retval.push_back(string(""));
            return retval;
        }
        
        string mychoices = (*(keyMap_.find(digits[0]))).second;
        vector<string> recurse = letterCombinationsPrime(digits.substr(1));
        
        vector<string> retval;
        for (unsigned int i=0; i<mychoices.length(); i++) {
            for (unsigned int j=0; j<recurse.size(); j++) {
                retval.push_back(string(1, mychoices[i]) + recurse[j]);
            }
        }
        return retval;
    }
    vector<string> letterCombinations(string digits) {
        if (digits == "") {
            vector<string> retval;
            return retval;
        }
        return letterCombinationsPrime(digits);
    }
};
