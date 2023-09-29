class Solution {
public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        int count = 0;
        for (const vector<string>& item : items) {
            if (ruleKey == "type" && item[0] == ruleValue) count++;
            if (ruleKey == "color" && item[1] == ruleValue) count++;
            if (ruleKey == "name" && item[2] == ruleValue) count++;
        }
        return count;
    }
};
