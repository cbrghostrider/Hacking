struct Info {
    int max_score=0;  // the max score so far
    int age=0;        // the age for which this is max score
    bool operator==(const Info& rhs) const {
        return (max_score == rhs.max_score && age == rhs.age);
    }
};

template<>
struct hash<Info> {
size_t operator()(const Info& info) const {
    return ((info.max_score << 10) | (info.age));
}
};

class Solution {                
    // at any index i, we can either take the player, or drop the player
    // if we take, we can only add the player to those values whose keys <= scores[i]
    
public:
    // O(n^2) time, O(n) space.
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        // indices sorted by age
        vector<int> indices;
        for (int i=0; i<scores.size(); i++)  {indices.push_back(i);}
        std::sort(indices.begin(), indices.end(), [&scores,&ages](int lhs, int rhs) -> bool {
            if (ages[lhs] != ages[rhs]) {return ages[lhs] < ages[rhs];}
            return scores[lhs] < scores[rhs];
        });
        
        // (max_score, age) -> points
        unordered_map<Info, int> info2pts;
        
        // Base case.
        info2pts[{0,0}] = 0;
        
        // DP.
        for (int i=0; i<indices.size(); i++)  {
            int index = indices[i];  
            int score = scores[index];
            int age = ages[index];
            
            // take it
            unordered_map<Info, int> info_take;
            for (const auto& kv : info2pts) {
                const auto& info = kv.first;
                int total = kv.second;
                if (info.max_score <= score || info.age == age) {
                    Info new_info;
                    new_info.max_score = std::max(info.max_score, score);
                    new_info.age = new_info.max_score == score ? age : info.age;
                    info_take[new_info] = std::max(info_take[new_info], total + score);
                }
            }
            
            // drop it -- this is same as info2pts
            
            // now merge info and info_take
            for (const auto& kv : info_take) {
                if (info2pts.find(kv.first) != info2pts.end()) {
                    info2pts[kv.first] = std::max(info2pts[kv.first], kv.second);
                } else {
                    info2pts[kv.first] = kv.second;
                }
            }
        }
        
        int biggest=0;
        for (const auto& kv : info2pts)  {
            biggest = std::max(biggest, kv.second);
        }
        return biggest;
    }    
};

