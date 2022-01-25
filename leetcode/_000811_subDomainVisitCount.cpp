class Solution {
public:
    // O(n*k) time, where n = |cpdomains|, k = |domain|.
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> data;
        for (const string& domain : cpdomains) {            
            int pos = domain.find_first_of(" ", 0);
            if (pos == string::npos) continue;  // error input
            int num = stoi(domain.substr(0, pos));
            
            pos++;
            int pos2 = domain.find_first_of(".", pos);
            if (pos == string::npos) continue;  // error input
            int len = pos2-pos;
            string d1 = domain.substr(pos, len);
            
            pos = pos2+1;
            pos2 = domain.find_first_of(".", pos);
            len = pos2 == string::npos ? domain.size()-pos : pos2-pos;
            string d2 = domain.substr(pos, len);
            
            string d3;
            if (pos2 != string::npos) {
                d3 = domain.substr(pos2+1);
                data[d3] += num;
                d2 += "." + d3;
            }
            data[d2] += num;
            d1 += "."+d2;
            data[d1] += num;
        }
        
        vector<string> ans;
        for (const auto& kv : data) {
            string a = to_string(kv.second) + " " + kv.first;
            ans.push_back(a);
        }
        return ans;
    }
};
