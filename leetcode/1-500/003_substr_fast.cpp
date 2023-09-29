// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) {
            return 0;
        }
        
        unsigned int max_len = 0;
        unsigned int cur_max = 0;
        unsigned int li = 0, ri = 0;  // left and right scanner pointers
        
        std::unordered_map<char, unsigned int> myMap; // mapping from char to index
        
        while (ri < s.size()) {
            if (myMap.find(s[ri]) == myMap.end()) {
                //couldn't find this char
                myMap[s[ri]] = ri;
                cur_max++;
            } else {
                if (cur_max > max_len) {
                    max_len = cur_max;
                }
                unsigned int repeated_index = myMap[s[ri]];
                while (li <= repeated_index) {
                    //drop the earlier letters, and reduce current max
                    myMap.erase(s[li]);
                    cur_max--;
                    li++;
                }
                myMap[s[ri]] = ri;
                cur_max++;
            }
            ri++;
        }
        if (cur_max > max_len) {
            max_len = cur_max;
        }
        return max_len;
    }
};
