class Solution {
    int minsSinceEpoch(const std::string& time) {
        int hrs = stoi(time.substr(0, 2));
        int mins = stoi(time.substr(3, 2));
        return (hrs*60 + mins);
    }
    
    int diffTime(const string& t1, const string& t2) {
        int e1 = minsSinceEpoch(t1);
        int e2 = minsSinceEpoch(t2);
        return std::abs(e1 - e2);
    }
    
    using MinHeap=priority_queue<string, vector<string>, std::greater<string>>;
    
    unordered_map<string, MinHeap> records;
    
public:
    // O(n log n) time, O(n) space.
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        
        vector<int> indices;
        for (int i=0; i<keyName.size(); i++) {
            indices.push_back(i);
        }
        std::sort(indices.begin(), indices.end(), [&keyTime](int lhs, int rhs) -> bool {
            return keyTime[lhs] < keyTime[rhs];
        });
        
        set<string> names;
        for (int i : indices) {
            MinHeap& mh = records[keyName[i]];
            while (!mh.empty() && diffTime(keyTime[i], mh.top()) > 60) {
                mh.pop();
            }
            mh.push(keyTime[i]);
            if (mh.size() >= 3) {
                names.insert(keyName[i]);
            }                  
        }
        vector<string> ans;
        for (const string& name : names) {ans.push_back(name);}

        return ans;
    }
};
