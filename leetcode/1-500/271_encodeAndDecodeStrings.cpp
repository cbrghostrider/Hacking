// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string retval;
        retval += to_string(strs.size()) + "_";
        for (const string& str : strs) {
            retval += to_string(str.size()) + "_";
            retval += str;
        }
        return retval;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> retval;
        size_t pos = s.find_first_of("_");
        if (pos == string::npos) return retval;
        int clen = std::stoi(s.substr(0, pos));
        pos++; //skip _
        
        for (int i=0; i<clen; i++) {
            size_t spos = s.find_first_of("_", pos);
            if (spos == string::npos) break;
            int slen = std::stoi(s.substr(pos, spos-pos));
            string pushme = s.substr(spos+1, slen);
            pos = spos+1+slen;
            retval.push_back(pushme);
        }
        return retval;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
