class Solution {
public:
    int lengthOfLastWord(string s) {
        //remove trailing whitespaces
        size_t size = s.find_last_not_of(" ");
        if (size == string::npos) return 0;
        s.erase(size+1);
        
        //find last word
        size = s.find_last_of(" ");
        return (size == string::npos ? s.length() : (s.length() - size - 1));
    }
};
