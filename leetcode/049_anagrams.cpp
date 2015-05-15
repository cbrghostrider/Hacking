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
