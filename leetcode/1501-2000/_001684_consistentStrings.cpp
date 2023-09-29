class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int consistent = 0;
        for (const string& word: words) {
            if (word.find_first_not_of(allowed) == string::npos) consistent++;
        }
        return consistent;
    }
};
