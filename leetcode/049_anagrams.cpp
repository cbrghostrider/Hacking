// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    //key is sorted string
    //value is vector of all strings that are anagrams of each other
    unordered_map<string, vector<string>> strSet;
public:
    vector<string> anagrams(vector<string>& strs) {
        vector<string> agset;
        for (string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            auto it = strSet.find(key);
            if (it == strSet.end()) {
                strSet[key] = vector<string>(1, str);
            } else {
                strSet[key].push_back(str);
            }
        }
        for (auto keyval : strSet) {
            if (keyval.second.size() > 1) {
                agset.insert(agset.end(), keyval.second.begin(), keyval.second.end());
            }
        }
        return agset;
    }
};
