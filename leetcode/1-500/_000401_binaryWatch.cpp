class Solution {
    
    string convert(int num) {
        int hours = ((0x3c0 & num) >> 6);
        int mins = (0x03F & num);
        if (hours > 11 || mins > 59) return "";
        string h = std::to_string(hours);
        string m = std::to_string(mins);
        if (m.size() == 1) {m = "0" + m;}
        return (h + ":" + m);
    }
    
    vector<int> getReprs(int turnedOn) {
        vector<int> ans;
        for (int i=0; i<1024; i++) {
            int count=0, mask=0x1;
            for (int p=0; p<10; p++) {
                if (mask & i) count++;
                mask <<= 1;
            }
            if (count == turnedOn) {ans.push_back(i);}
        }
        return ans;
    }
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<int> reprs = getReprs(turnedOn);
        vector<string> ans;
        for_each(reprs.begin(), reprs.end(), [&ans, this](int c) {
            string s = convert(c);
            if (!s.empty()) ans.push_back(s);
        });
        return ans;
    }
};
