class Solution {    
    
    using Distro = unordered_map<char, int>;
    // index -> freqs of chars in words[index]
    unordered_map<int, Distro> freqs;
    
    // char -> indices of words containing char
    unordered_map<char, unordered_set<int>> contained_in;
    
    // memoization cache
    // signature -> count
    unordered_map<string, int> cache;
    
    string signature(const Distro& distro) {
        string ret;
        for (const auto& kv : distro) {
            ret += string(1, kv.first) + to_string(kv.second) + ":";
        }
        return ret;
    }    
    
    int minWords(Distro distro) {
        if (distro.empty()) {return 0;}
        string sig = signature(distro);
        if (cache.find(sig) != cache.end()) {return cache[sig];}
        
        int best=std::numeric_limits<int>::max();
        char ch = distro.begin()->first;        
        for (int ind : contained_in[ch]) {            
            Distro my_distro = distro;
            for (const auto& kv : freqs[ind]) {
                if (my_distro.find(kv.first) != my_distro.end()) {
                    my_distro[kv.first] -= std::min(kv.second, my_distro[kv.first]);
                    if (my_distro[kv.first] == 0) {my_distro.erase(kv.first);}
                }
            }
            int my_count = 1 + minWords(my_distro);
            best = std::min(best, my_count);
        }
        
        cache[sig] = best;
        return best;
    }
    
public:
    int minStickers(vector<string>& stickers, string target) {
        // Initialization.
        for (int i=0; i<stickers.size(); i++) {
            const string& word = stickers[i];                        
            
            for (char ch : word) {
                freqs[i][ch]++;
                contained_in[ch].insert(i);
            }            
        }
                
        Distro distro;
        for (char ch : target) {
            distro[ch]++;
            if (contained_in.find(ch) == contained_in.end()) {return -1;}
        }
        
        int count = minWords(distro);
        return count;
    }
};
