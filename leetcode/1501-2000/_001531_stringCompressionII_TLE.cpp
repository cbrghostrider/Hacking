struct Info {
    string rle;
    int k_left=0;
    bool operator==(const Info& rhs) const {
        return (rle == rhs.rle && k_left == rhs.k_left);
    }
    bool operator!=(const Info& rhs) const {
        return !(*this == rhs);
    }
}; 

template<>
struct hash<Info> {
size_t operator()(const Info& info) const {
    std::hash<string> str_hash;
    size_t  ret = str_hash(info.rle) ^ (size_t)(info.k_left);
    return ret;
}
};

class Solution {    
    const string letters = "abcdefghijklmnopqrstuvwxyz";    
public:    
    
    int getLengthOfOptimalCompression(string s, int k) {
        unordered_set<Info> dp;
        
        // Base case.
        dp.insert({"", k});
        
        // DP.
        for (int i=0; i<s.size(); i++) {
            char ch = s[i];
            unordered_set<Info> new_dp;
            
            for (const Info& info : dp) {
                // take it
                Info ninfo = info;
                int pos = info.rle.find_last_of(letters);                
                if (pos == string::npos || info.rle[pos] != ch) {
                    ninfo.rle += string(1, ch);
                } else {
                    int val = pos == info.rle.size() - 1 ? 2 : stoi(info.rle.substr(pos+1)) + 1;
                    ninfo.rle = info.rle.substr(0, pos+1) + to_string(val);
                }
                new_dp.insert(ninfo);
                
                // drop it if you can
                if (info.k_left > 0) {
                    Info ninfo = info;
                    ninfo.k_left--;
                    new_dp.insert(ninfo);
                }
            }
            std::swap(dp, new_dp);
            new_dp.clear();
        }
        
        // Find min rle string
        int best=std::numeric_limits<int>::max();
        for (const Info& info : dp) {
            best = std::min(best, (int)info.rle.size());
        }
        return best;
    }
    
    
};
