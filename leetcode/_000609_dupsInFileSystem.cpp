class Solution {
    vector<string> words(const string& str) {
        vector<string> ret;
        int pos=0;
        while (pos < str.size() && pos != string::npos) {
            int end = str.find_first_of(" ", pos);
            int len = end == string::npos ? str.size()-pos : end-pos;
            ret.push_back(str.substr(pos, len));
            if (end == string::npos) break;
            pos = end+1;
        }
        return ret;
    }
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> content_to_files;
        
        for (const string& pinfo : paths) {
            vector<string> list = words(pinfo);
            for (int i=1; i<list.size(); i++) {
                int pos = list[i].find_first_of("(");
                string file = list[0] + "/" + list[i].substr(0, pos);
                string content = list[i].substr(pos+1, list[i].size()-1 - (pos+1));  // assumes content non-empty
                content_to_files[content].push_back(file);
            }
        }
        
        vector<vector<string>> ans;
        for (const auto& kv : content_to_files) {
            if (kv.second.size() > 1) ans.push_back(kv.second);
        }
        return ans;
    }
};
