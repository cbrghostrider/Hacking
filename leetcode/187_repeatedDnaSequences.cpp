//using string as map key gives memory limit exceeded
//but pre-hashing that string to a size_t works fine!
//weird!!
class Solution {
    unordered_map<size_t, int> seqCount;
    vector<string> strMap;
public:
    vector<string> findRepeatedDnaSequences(string s) {
        std::hash<std::string> strHash;
        if (s.length() < 10) return vector<string>();
        for (int ind=0; ind <= s.length() - 10; ind++) {
            string cand = s.substr(ind, 10);
            auto it = seqCount.find(strHash(cand));
            if (it == seqCount.end()) {
                seqCount[strHash(cand)] = 1;
            } else {
                seqCount[strHash(cand)] += 1;
                if (seqCount[strHash(cand)] == 2) {
                    strMap.push_back(cand);
                }
            }
        }
        return strMap;
    }
};
