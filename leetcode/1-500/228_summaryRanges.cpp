// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    string createRange(int start, int rangeLength) {
        string str = std::to_string(start); 
        if (rangeLength > 1) {
            str += "->"; str += std::to_string(start + rangeLength - 1);
        }
        return str;
    }
    vector<string> summaryRanges(vector<int>& nums) {
        if (nums.empty()) return vector<string>();
        
        vector<string> ranges;
        int rangeLength = 1;
        int start = nums[0];
        
        for (int i=1; i<nums.size(); i++) {
            int n = nums[i];
            if (n == start+rangeLength) { //range continues
                rangeLength++;    
            } else { //range ended
                //record current range
                ranges.push_back(createRange(start, rangeLength));
                
                //and reset state
                start = n;
                rangeLength = 1;
            }
        }
        ranges.push_back(createRange(start, rangeLength));
        return ranges;
    }
};
