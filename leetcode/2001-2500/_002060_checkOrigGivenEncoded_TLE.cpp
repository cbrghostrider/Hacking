class Solution {
    using Mappings=unordered_map<int, char>;
    using Tag=int;
    
    const string digits="123456789";  // no 0 as per problem
    const string letters = "abcdefghijklmnopqrstuvwxyz";
    
    struct Elem {
        bool is_string=true;
        string str_val;
        int num=0;
        
        int length() const {
            if (is_string) return str_val.size();
            return num;
        }
    };
    struct Encoding {
        vector<Elem> elems;
        
        int length() const {
            int len=0;
            for (const Elem& e : elems) {len += e.length();}
            return len;
        }
        
        Mappings getMappings() const {
            Mappings ret;
            int ctr=0;
            for (const Elem& elem : elems) {
                if (!elem.is_string) {
                    ctr += elem.length();
                    continue;
                }
                for (int i=0; i<elem.str_val.size(); i++) {                    
                    ret[ctr++] = elem.str_val[i];
                }
            }
            return ret;
        }
    };
    
    // Takes a numstr like "1234" and breaks it up into all encodings like:
    // 123, 4; .....; 12, 34; 1, 2, 34; 1, 234;
    // split backwards from "from"    
    vector<Encoding> splitNums(const string& s, int from) {
        if (from == 0) {
            Encoding ret;
            ret.elems.push_back(Elem());
            ret.elems.back().is_string = false;
            ret.elems.back().num = stoi(string(1, s[from]));
            return {ret};
        }
        
        vector<Encoding> encodings;
        int sz_limit = from+1;
        for (int sz=1; sz<sz_limit; sz++) {
            Elem elem;
            elem.is_string = false;
            int start = from-sz+1;
            elem.num = stoi(s.substr(start, sz));
            
            vector<Encoding> recurse = splitNums(s, from-sz);
            for (Encoding& enc : recurse) {
                enc.elems.push_back(elem);
            } 
            encodings.insert(encodings.end(), recurse.begin(), recurse.end());
        }
        
        // The whole number itself is also an encoding.
        Elem elem;
        elem.is_string = false;
        elem.num = stoi(s.substr(0, from+1));
        encodings.push_back(Encoding());
        encodings.back().elems.push_back(elem);
        
        return encodings;
    }
    
    // returns all the encodings of s[from...end]
    vector<Encoding> getEncodings(const string& s, int from) {
        if (from >= s.size()) {
            Encoding ret;            
            ret.elems.push_back(Elem());  // exactly 1 empty string element
            return {ret};
        };
        
        vector<Encoding> encodings;
        encodings.push_back(Encoding());
        
        int s_ptr=0;
        while (s_ptr < s.size() && s_ptr != string::npos) {
            
            if (std::isalpha(s[s_ptr])) {
                int pos = s.find_first_of(digits, s_ptr);
                int len = pos == string::npos ? s.size()-s_ptr : pos - s_ptr;
                string str = s.substr(s_ptr, len);
                for_each(encodings.begin(), encodings.end(), [&str](Encoding& enc) {
                    enc.elems.push_back(Elem());
                    enc.elems.back().str_val = str;
                });
                s_ptr += len;
                continue;
            }
            
            int pos = s.find_first_of(letters, s_ptr);
            int len = pos == string::npos ? s.size()-s_ptr : pos-s_ptr;
            string str = s.substr(s_ptr, len);
            s_ptr += len;
            
            vector<Encoding> splits = splitNums(str, str.size()-1);
            vector<Encoding> temp;
            for (const Encoding& encoding : encodings) {
                for (Encoding& split : splits) {
                    temp.push_back(encoding);
                    temp.back().elems.insert(temp.back().elems.end(), split.elems.begin(), split.elems.end());
                }
            }
            std::swap(encodings, temp);
            temp.clear();
        }
        
        return encodings;
    }
    
public:
    // Solution is functionally correct.
    // 96/215 cases pass currently.
    bool possiblyEquals(string s1, string s2) {
        string num="389";
        auto aaa = splitNums(num, 2);
        vector<Encoding> s1_encs = getEncodings(s1, 0);
        vector<Encoding> s2_encs = getEncodings(s2, 0);
        
        unordered_map<Tag, Mappings> s1_maps;
        unordered_map<Tag, Mappings> s2_maps;
        
        for (int i=0; i<s1_encs.size(); i++) {
            s1_maps[i] = s1_encs[i].getMappings();
        }
        for (int i=0; i<s2_encs.size(); i++) {
            s2_maps[i] = s2_encs[i].getMappings();
        }
        
        for (int i=0; i<s1_encs.size(); i++) {
            const Encoding& e1 = s1_encs[i];
            
            for (int j=0; j<s2_encs.size(); j++) {
                const Encoding& e2 = s2_encs[j];
                
                if (e1.length() != e2.length()) {
                    continue;  // mismatch
                }
                
                Mappings& m1 = s1_maps[i];
                Mappings& m2 = s2_maps[j];
                
                bool match = true;
                for (const auto& kv : m1) {
                    int pos = kv.first;
                    char let = kv.second;
                    if (m2.find(pos) != m2.end() && m2[pos] != let) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    return true;  // matched all letters (checking one map is enough)
                }
            }            
        }
        return false;
    }
};
