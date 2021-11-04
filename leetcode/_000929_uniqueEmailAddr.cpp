class Solution {
    unordered_set<string> addresses;
    
    void sanitize(string& name) {
        name = name.substr(0, name.find_first_of("+"));
        string new_name;
        std::for_each(name.begin(), name.end(), [&new_name](char c) {
            if (c != '.') new_name.push_back(c);
        });
        name = new_name;
    }
    
public:
    
    // O(s * n) time, O(s * n) space.
    int numUniqueEmails(vector<string>& emails) {
        for (string addr : emails) {
            int d_pos = addr.find_first_of("@");
            if (d_pos == string::npos) continue;  // malformed addr.
            string domain = addr.substr(d_pos);
            string name = addr.substr(0, d_pos);
            sanitize(name);
            addresses.insert(name+domain);
        }
        return addresses.size();
    }
};
