class Solution {
    struct Info {
        int index;      // balloon-id
        int val;        // the coordinate (start or end)
        bool is_start;  // whether val is start or end
    };
public:
    // O(n log n) time, O(n) space.
    int findMinArrowShots(vector<vector<int>>& points) {
        vector<Info> infos;
        for (int i=0; i<points.size(); i++) {
            infos.push_back({i, points[i][0], true});
            infos.push_back({i, points[i][1], false});
        }
        std::sort(infos.begin(), infos.end(), [](const Info& lhs, const Info& rhs) -> bool {
            if (lhs.val != rhs.val) return lhs.val < rhs.val;
            if (lhs.is_start != rhs.is_start) {
                if (lhs.is_start) return true;
                return false;
            }
            return lhs.index < rhs.index;
        });
        
        vector<bool> burst(points.size(), false);
        vector<int> in_progress;
        int arrows=0;
        for (int i=0; i<infos.size(); i++) {
            if (infos[i].is_start) {
                in_progress.push_back(infos[i].index);
                continue;
            } 
            
            // This balloon was already taken out, no need to waste arrows.
            if (burst[infos[i].index]) {continue;}
            
            // shoot a balloon and take out everything in progress
            arrows++;
            for (int balloon : in_progress) {
                burst[balloon] = true;
            }
        }
        return arrows;
    }
};
