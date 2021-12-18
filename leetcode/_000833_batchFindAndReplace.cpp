class Solution {
    struct Info {
        int index=-1;
        string source;
        string target;
    };
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        if (indices.size() == 0) return s;
        
        vector<Info> infos;
        int delta=0;
        for (int i=0; i<indices.size(); i++) {
            // worst case, overestimation, because we don't know if replacement will occur yet
            delta += std::max(sources[i].size(), targets[i].size());   
            infos.push_back({indices[i], sources[i], targets[i]});
        }
        std::sort(infos.begin(), infos.end(), [](const Info& lhs, const Info& rhs) -> bool {
            return lhs.index < rhs.index;
        });
        
        string ret;
        ret.reserve(s.size() + delta);
        
        if (infos[0].index != 0) {
            ret += s.substr(0, infos[0].index);
        }
        for (int i=0; i<infos.size(); i++) {
            const Info& info = infos[i];
            int end_index = (i == infos.size()-1 ? s.size() : infos[i+1].index);
            
            if (s.substr(info.index, info.source.size()) != info.source) {
                // put everything from here to the next info into ret    
                ret += s.substr(info.index, end_index - info.index);
                continue;
            }
            ret += info.target;
            int start_index = info.index + info.source.size();
            ret += s.substr(start_index, end_index-start_index);
        }
        
        return ret;
    }
};
