class Solution {
    struct Info {
        int num_vals=0;
        int from=0;
        int to=0;
        bool reversed=false;
    };    
    
public:
    // O(log n) time, O(log n) space.
    vector<int> pathInZigZagTree(int label) {        
        vector<Info> lvlInfo;
        
        int running_count=1;  // across all rows
        int num=1;  // in each row
        lvlInfo.push_back({1, 1, 1, false});
        
        while (running_count < label) {
            num <<= 1;  // multiply by 2
            int last_label = lvlInfo.back().to;
            int start = last_label + 1;
            int end = start + num - 1;
            bool my_reversed = !lvlInfo.back().reversed;
            Info curr = {num, start, end, my_reversed};            
            lvlInfo.push_back(curr);
            running_count = end;
        }
        
        int pos = label - lvlInfo.back().from;
        if (lvlInfo.back().reversed) {
            pos = num - 1 - pos;
        }
        
        vector<int> indices;
        while (num) {
            indices.push_back(pos);
            pos /= 2;
            num >>= 1;
        }
        std::reverse(indices.begin(), indices.end());
        
        vector<int> ans;
        for (int i=0; i<indices.size(); i++) {
            int index = lvlInfo[i].reversed ? lvlInfo[i].num_vals - 1 - indices[i] : indices[i];
            int val = lvlInfo[i].from + index;
            ans.push_back(val);
        }
        return ans;
    }
};
