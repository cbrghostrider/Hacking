class Solution {
    string s1, s2;
    using Signature=uint32_t;
    
    struct Info {        
        int next=0;  // the next index to consume in encoded string, only used if num=0
        int num=0;   // before we consume next index, we have num positions to give out
        
        Signature signature() const {
            return ((next << 16) | (num));
        }
    };
    
    // called when the next ptr is pointing to numeric
    // and when the next ptr is ready to be consumed
    // Returns results greedily! The largest number first, so we can try to match greedy.
    vector<Info> getOptions(const string& s, Info info) {
        assert(isdigit(s[info.next]));
        vector<Info> options;
        
        // Push 3 digit number
        if (info.next < s.size()-2 && isdigit(s[info.next+1]) && isdigit(s[info.next+2])) {
            Info op = {info.next+3, stoi(s.substr(info.next, 3))};
            options.push_back(op);
        }                
        
        // Push 2 digit number
        if (info.next < s.size()-1 && isdigit(s[info.next+1])) {
            Info op = {info.next+2, stoi(s.substr(info.next, 2))};
            options.push_back(op);
        }
        
        // Push single digit number.
        Info op = {info.next+1, stoi(string(1, s[info.next]))};
        options.push_back(op);

        return options;
    }
    
    // key1: signature of s1 positioning
    // key2: signature of s2 positioning
    // value: if this works or not
    unordered_map<Signature, unordered_map<Signature, bool>> cache;
    
    bool matches(Info p1, Info p2) {

        Signature sig1 = p1.signature();
        Signature sig2 = p2.signature();
        if (cache[sig1].find(sig2) != cache[sig1].end()) {
            return cache[sig1][sig2];
        }
        
        bool p1_done = (p1.next >= s1.size() && p1.num == 0);
        bool p2_done = (p2.next >= s2.size() && p2.num == 0);
        
        if (p1_done && p2_done) {  // both matched perfectly at the end
            cache[sig1][sig2] = true;
            return true;
        }
        if (p1_done || p2_done) {  // one was left unmatched content
            cache[sig1][sig2] = false;
            return false;
        }
        
        bool ans=false;
        
        if (p1.num > 0 && p2.num > 0) {
            int remove = std::min(p1.num, p2.num);
            p1.num -= remove; 
            p2.num -= remove;
            ans = matches(p1, p2);
        } else if (p1.num > 0) {
            // Process p2's next
            if (std::isalpha(s2[p2.next])) {  // match this alpha
                p2.next++;
                p1.num--;
                ans = matches(p1, p2);
            } else {
                vector<Info> options2 = getOptions(s2, p2);
                for (Info op : options2) {
                    ans = matches(p1, op);
                    if (ans == true) {break;}
                }                
            }
        } else if (p2.num > 0) {
            // Process p1's next
            if (std::isalpha(s1[p1.next])) {  // match this alpha
                p1.next++;
                p2.num--;
                ans = matches(p1, p2);
            } else {
                vector<Info> options1 = getOptions(s1, p1);
                for (Info op : options1) {
                    ans = matches(op, p2);
                    if (ans == true) {break;}
                }                
            }
        } else if (isalpha(s1[p1.next]) && isalpha(s2[p2.next])) {
            ans = s1[p1.next] == s2[p2.next];
            if (ans) {  // only then recurse
                p1.next++;
                p2.next++;
                ans = matches(p1, p2);
            }
        } else if (isalpha(s1[p1.next])) {
            vector<Info> options2 = getOptions(s2, p2);
            for (Info op : options2) {
                ans = matches(p1, op);
                if (ans == true) {break;}
            }                
        } else if (isalpha(s2[p2.next])) {
            vector<Info> options1 = getOptions(s1, p1);
            for (Info op : options1) {
                ans = matches(op, p2);
                if (ans == true) {break;}
            }              
        } else {
            vector<Info> options1 = getOptions(s1, p1);
            vector<Info> options2 = getOptions(s2, p2);
            bool done = false;
            for (Info op1 : options1) {
                for (Info op2 : options2) {
                    if (done) continue;
                    ans = matches(op1, op2);
                    if (ans == true) {done = true;}
                }            
            }
        }
        
        cache[sig1][sig2] = ans;
        return ans;
    }
    
public:
    // 215/215 cases passed! 
    // But OJ still says TLE (across total time instead of individual).
    bool possiblyEquals(string str1, string str2) {
        s1 = str1;
        s2 = str2;
        
        Info info1 = {0, 0};
        Info info2 = {0, 0};
        
        bool ans = matches(info1, info2);
        return ans;
    }
};
