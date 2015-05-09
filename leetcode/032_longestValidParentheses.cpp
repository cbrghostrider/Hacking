class Solution {
public:
    int longestValidParentheses(string s) {
	if (s.size() == 0) return 0;
        bool validArr_[s.size()];   //array to record which '(' or ')' match up w/ each other
        vector<int> openLocations_; //stack to record opened parentheses '(' locations
        for (int i=0; i<s.size(); i++) {
            if (s[i] == '(') { 
                openLocations_.push_back(i);
                validArr_[i] = false;
            } else {
                if (!openLocations_.empty()) {
                    int matchingOpen = openLocations_.back(); openLocations_.pop_back();
                    validArr_[i] = validArr_[matchingOpen] = true;
                } else{
                    validArr_[i] = false;
                }
            }
        }
        int maxSeqLen = 0, ctr=0;
        for (int i=0; i<s.size(); i++) {
            if (validArr_[i] == false) {
                if (ctr > maxSeqLen) {
                    maxSeqLen = ctr;
                }
                ctr=0;
            } else {
                ctr++;
            }
        }
        if (validArr_[s.size()-1] == true && ctr > maxSeqLen) {
            maxSeqLen = ctr;
        }
        return maxSeqLen;
    }
};
