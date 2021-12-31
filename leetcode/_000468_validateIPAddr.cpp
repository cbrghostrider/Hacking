class Solution {
    bool isIP6Comp(const string& val) {
        if (val.size() > 4 || val.size() < 1) return false;
        int pos = val.find_first_not_of("0123456789abcdefABCDEF");
        if (pos != string::npos) return false;
        return true;
    }
    
    bool checkIP6(const string& addr) {
        int s_ptr=0;        
        for (int i=0; i<7 && s_ptr<addr.size(); i++) {
            int pos = addr.find_first_of(":", s_ptr);
            if (pos == string::npos) return false;
            string val = addr.substr(s_ptr, pos-s_ptr);
            if (!isIP6Comp(val)) return false;
            s_ptr = pos+1;
        }  
        if (s_ptr >= addr.size()) return false;
        string val = addr.substr(s_ptr);
        if (!isIP6Comp(val)) return false;
        return true;        
    }
    
    bool isIP4Comp(const string& val) {
        if (val.size() == 0 || val.size()>3) return false;
        for (char ch : val) {if (!std::isdigit(ch)) return false;}
        if (val.size() > 1 && val[0] == '0') return false;
        int num = std::stoi(val);
        if (num < 0 || num > 255) return false;
        return true;
    }
    
    bool checkIP4(const string& addr) {        
        int s_ptr=0;        
        for (int i=0; i<3 && s_ptr<addr.size(); i++) {
            int pos = addr.find_first_of(".", s_ptr);
            if (pos == string::npos) return false;
            string val = addr.substr(s_ptr, pos-s_ptr);
            if (!isIP4Comp(val)) return false;
            s_ptr = pos+1;            
        }
        if (s_ptr >= addr.size()) return false;
        string val = addr.substr(s_ptr);
        if (!isIP4Comp(val)) return false;
        return true;
    }
    
public:
    string validIPAddress(string queryIP) {
        if (queryIP.size() == 0) return "Neither";
        if (checkIP4(queryIP)) {return "IPv4";}
        if (checkIP6(queryIP)) {return "IPv6";}
        return "Neither";
    }
};
