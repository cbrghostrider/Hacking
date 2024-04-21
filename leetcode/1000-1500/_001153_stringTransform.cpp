class Solution {

vector<int> conv_positional(const string& str) {
    unordered_map<char, int> freqs;
    for (char ch : str) {
        if (freqs.find(ch) == freqs.end()) freqs[ch] = 1; else freqs[ch]++;
    }
    vector<int> ret(str.size(), 0);
    for (int i=0; i<str.size(); i++) {ret[i] = freqs[str[i]];}
    return ret;
}

// Impossible if one src char needs to turn into 2 dst chars.
// Src char can change, but the freq (of the changed) cannot be greater than the freq in the dest for that char.
bool is_impossible(const vector<int>& src, const vector<int>& dst) {
    for (int i=0; i<src.size(); i++) {
        if (src[i] > dst[i]) return true;
    }
    return false;  // may be possible
}

public:
    bool canConvert(string str1, string str2) {
        if (str1.size() != str2.size()) return false;
        if (str1 == str2) return true;
        vector<int> pos_str1 = conv_positional(str1);
        vector<int> pos_str2 = conv_positional(str2);
        if (is_impossible(pos_str1, pos_str2)) return false;        

        // Find letters in dest, but not in src.
        std::map<char, int> src_chars, dst_chars;
        for (char ch : str1) {src_chars[ch]++;}
        for (char ch : str2) {dst_chars[ch]++;}
        vector<pair<char, int>> sdchars;
        std::set_difference(dst_chars.begin(), dst_chars.end(), src_chars.begin(), src_chars.end(), std::back_inserter(sdchars));
        if (sdchars.size() > 1) return true;
        if (dst_chars.size() < 26) return true;  // if not all chars are used, we can convert a src char to a temporarily unused char name
        return false;        
    }
};
