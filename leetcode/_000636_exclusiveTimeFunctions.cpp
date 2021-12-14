class Solution {
    struct Info {
        int fn;
        int time;
        string op;
    };
    
    Info processLog(const string& log) {
        int pos = log.find_first_of(":");
        int fn = std::stoi(log.substr(0, pos));
        pos++;
        int pos2 = log.find_first_of(":", pos);
        string op = log.substr(pos, pos2-pos);
        pos2++;
        int time = std::stoi(log.substr(pos2));
        return {fn, time, op};
    }
    
public:
    
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> fn_ids;
        unordered_map<int, vector<int>> timepoints;
        
        for (const string& log : logs) {
            Info info = processLog(log);
            if (info.op == "start") {
                if (!fn_ids.empty()) {
                    int prev_fn = fn_ids.back();
                    timepoints[prev_fn].push_back(info.time-1);  // previous function pauses here
                }
                fn_ids.push_back(info.fn);
                timepoints[info.fn].push_back(info.time);  // current function starts here
            } else {  // info.op == "end"
                timepoints[info.fn].push_back(info.time);  // current function ends here
                fn_ids.pop_back();
                if (!fn_ids.empty()) {
                    timepoints[fn_ids.back()].push_back(info.time+1);  // previous function unpauses here
                }
            }
        }
        
        vector<int> ans(n, 0);
        for (const auto& kv : timepoints) {
            int fn = kv.first;
            const vector<int>& vals = kv.second;
            for (int i=0; i<vals.size(); i+=2) {
                ans[fn] += vals[i+1] - vals[i] + 1;
            }
        }
        return ans;
    }
};
