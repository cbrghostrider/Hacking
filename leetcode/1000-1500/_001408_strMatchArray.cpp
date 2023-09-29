class Solution {
    bool isSubstrOf(const string& haystack, const string& needle) {
        if (needle.size() > haystack.size()) return false;
        int nsz = needle.size();
        for (int i=0; i+nsz<=haystack.size(); i++) {
            if (needle == haystack.substr(i, nsz)) return true;
        }
        return false;
    }
public:
    vector<string> stringMatching(vector<string>& words) {
        std::sort(words.begin(), words.end(), [](const string& lhs, const string& rhs) -> bool {
            if (lhs.size() != rhs.size()) return lhs.size() < rhs.size();
            return lhs < rhs;
        });
        vector<string> ans;
        for (int i=0; i<words.size(); i++) {
            const string& needle = words[i];
            for (int j=i+1; j<words.size(); j++) {
                const string& haystack = words[j];
                if (isSubstrOf(haystack, needle)) {
                    ans.push_back(needle);
                    break;
                }
            }
        }
        return ans;
    }
};
