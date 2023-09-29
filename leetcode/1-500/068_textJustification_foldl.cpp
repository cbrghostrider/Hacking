// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//for shits and giggles, using a few left folds
//code is NOT readable, and I will likely re-write this later!
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        if (words.size() == 0) return vector<string>();
        if (maxWidth == 0) return words;
        //accumulator stores lines, and unconsumed words thus far
        auto acc = make_pair(vector<string>(), vector<string>());
        
        auto result = std::accumulate(words.begin(), words.end(), acc, [maxWidth] 
            (const pair<vector<string>, vector<string>>& acc, const string& word) -> pair<vector<string>, vector<string>> {
                auto lines       = acc.first;
                auto unconsumWds = acc.second;
                int len = std::accumulate(unconsumWds.begin(), unconsumWds.end(), 0, [] (const int& ac, const string& w) -> int {
                   return (ac + w.length());
                });

                int wspaces = unconsumWds.size() ? (unconsumWds.size() - 1) : 0;
                int clen = len + wspaces + word.length() + (unconsumWds.size() ? 1: 0);
                if ((clen) <= maxWidth) {
                    unconsumWds.push_back(word);
                    return (make_pair(lines, unconsumWds));
                } 
                
                if (unconsumWds.size() == 1) {
                    string thisline = unconsumWds[0];
                    if (maxWidth > unconsumWds[0].length()) 
                        thisline += string((maxWidth - unconsumWds[0].length()) , ' ');
                    lines.push_back(thisline);
                    return (make_pair(lines, vector<string>(1, word)));
                }
                
                int i=0, spaces = maxWidth - len;
                string thisline;                
                for (i=0; i<unconsumWds.size()-1; i++) {
                    int ns = spaces / (unconsumWds.size()-i-1);
                    int ls = spaces % (unconsumWds.size()-i-1);
                    if (ls) {
                        thisline = thisline + unconsumWds[i] + string(ns+1, ' '); 
                        spaces = spaces - (ns+1);
                    } else {
                        thisline = thisline + unconsumWds[i] + string(ns, ' ');
                        spaces = spaces - ns;
                    }
                }
                thisline += unconsumWds[i];
                lines.push_back(thisline);
                return (make_pair(lines, vector<string>(1, word)));
            });
        string final; 
        if (result.second.size()) { 
            final = std::accumulate(result.second.begin() + 1, result.second.end(), result.second[0], 
            [] (const string& acc, const string& word) -> string {
                return (acc + " " + word);
            });
            int leftlen = maxWidth - final.length();
            final = final + string(leftlen, ' ');
        }
        if (final.length()) result.first.push_back(final);
        return (result.first);
    }
};


