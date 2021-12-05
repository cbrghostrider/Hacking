class Solution {
    unordered_map<string, string> url_to_hash;
    unordered_map<string, string> hash_to_url;
    
    bool init=false;
    const unsigned int seed = 0xdeadbeef;
    const string choices = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    string gen16StrInternal() {
        string ret;
        for (int i=0; i<16; i++) {
            int index = std::rand() % choices.size();
            ret.push_back(choices[index]);
        }
        return ret;
    }
    
    string genRandom16Str() {
        if (!init) { srand(seed); init = true; }
        
        string hval;
        do {
            hval = gen16StrInternal();
            hval = "https://tinyurl.com/" + hval;
        } while (hash_to_url.find(hval) != hash_to_url.end());        
        
        return hval;
    }
    
public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string hval = genRandom16Str();
        url_to_hash[longUrl] = hval;
        hash_to_url[hval] = longUrl;
        return hval;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return hash_to_url[shortUrl];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
