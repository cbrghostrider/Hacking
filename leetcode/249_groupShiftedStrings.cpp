// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
private:
    const int SETSIZE = 26;
    typedef string Sequence;
    unordered_map<string, vector<string>> results;

    //will convert each string to a list of displacements
    Sequence getSequence(const string& str) {
        if (str.length() == 0)  { return ""; }
        if (str.length() == 1)  { return "="; }
        string retval;
        for (int i=1; i<str.size(); i++) {
            int diff = ((str[i] - str[i-1]) + SETSIZE) % SETSIZE;
            retval += std::to_string(diff) + ",";
        }
        return retval;
    }
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        if (strings.size() == 0) return vector<vector<string>>();

        for (const string& str : strings) {
            Sequence seq = getSequence(str);
            auto it = results.find(seq);
            if (it == results.end()) {
                vector<string> pushme;
                pushme.push_back(str);
                results.insert(make_pair(seq, pushme));
            } else {
                results[seq].push_back(str);
            }
        }

        vector<vector<string>> retval;
        for (const pair<string, vector<string>>& melem : results ) {
            vector<string> pushme = melem.second;
            std::sort(pushme.begin(), pushme.end());
            retval.push_back(pushme);
        }
        
        return retval;
    }
};



