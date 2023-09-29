class Solution {
    // Represent a sequence of letters in a run-length-encoded form.
    struct Rle {
        char ch=' ';
        int run=0;
    };
    
    vector<Rle> convert(const string& s) {
        vector<Rle> rle;
        int s_ptr=0;
        while (s_ptr < s.size()) {
            int e_ptr = s_ptr;
            while (e_ptr < s.size() && s[s_ptr] == s[e_ptr]) {
                e_ptr++;
            }
            rle.push_back({s[s_ptr], e_ptr-s_ptr});
            s_ptr = e_ptr;
        }
        return rle;
    }
    
public:
    int expressiveWords(string s, vector<string>& words) {
        vector<Rle> s_rle = convert(s);
        
        int count=0;
        for (const string& word : words) {
            vector<Rle> w_rle = convert(word);
            if (s_rle.size() != w_rle.size()) continue;
            bool stretchy = true;
            for (int i=0; i<s_rle.size(); i++) {
                if (s_rle[i].ch != w_rle[i].ch) {
                    stretchy = false; break;
                }
                if (s_rle[i].run != w_rle[i].run && 
                    (s_rle[i].run < w_rle[i].run || s_rle[i].run < 3)) {
                    stretchy = false; break;
                }                
            }
            if (stretchy) {count++;}
        }
        return count;
    }
};
