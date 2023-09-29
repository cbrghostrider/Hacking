class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        if (words.size() <= 1) return true;
        
        unordered_map<char, int> ordering;
        for (int i=0; i<order.size(); i++) {ordering[order[i]] = i;}
        
        string last = words[0];
        for (int i=1; i<words.size(); i++) {
            const string& curr = words[i];
            int ptr = 0;
            while (ptr < last.size() && ptr < curr.size()) {
                if (ordering[last[ptr]] > ordering[curr[ptr]]) {
                    return false;
                } else if (ordering[last[ptr]] < ordering[curr[ptr]]) {
                    break;
                } else {
                    ptr++;
                }
            }
            if (ptr == std::min(last.size(), curr.size()) && last.size() > curr.size()) {
                return false;
            }
            last = curr;
        }
        return true;
    }
};
