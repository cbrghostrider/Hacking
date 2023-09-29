class Solution {

    bool b_occludes_a(const vector<vector<int>>& peaks, int a_ind, int b_ind) {
        int bx=peaks[b_ind][0], by=peaks[b_ind][1];
        int ax=peaks[a_ind][0], ay=peaks[a_ind][1];
        int delta_x = std::abs(bx-ax);
        int b_y_at_a = by - delta_x;
        return (b_y_at_a >= ay);
    }

public:
    int visibleMountains(vector<vector<int>>& peaks) {
        // Sort peaks on x coord.
        std::sort(peaks.begin(), peaks.end(), [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[0] == rhs[0]) {
                return lhs[1] < rhs[1];
            }
            return lhs[0] < rhs[0];
        });
        
        unordered_set<int> occluded;        
        // indices of peaks.
        vector<int> mono;

        // How many are occluded, going from left to right.
        for (int i=0; i<peaks.size(); i++) {
            while (!mono.empty() && b_occludes_a(peaks, mono.back(), i)) {                
                occluded.insert(mono.back());
                mono.pop_back();
            }
            mono.push_back(i);
        }

        mono.clear();
        // How many are occluded, going from right_to_left;
        for (int i=peaks.size()-1; i>=0; i--) {
            while (!mono.empty() && b_occludes_a(peaks, mono.back(), i)) {                
                occluded.insert(mono.back());
                mono.pop_back();
            }
            mono.push_back(i);
        }        

        return peaks.size() - occluded.size();
    }
};
