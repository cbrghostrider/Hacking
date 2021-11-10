class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int dist = std::max(std::abs((long)(nums.size()-1 - start)), std::abs((long)(start-0)));
        for (int d=0; d<=dist; d++) {
            int bw_index = start-d;
            int fw_index = start+d;
            if (bw_index >=0 && nums[bw_index] == target) return d;
            if (fw_index < nums.size() && nums[fw_index] == target) return d;
        }
        return -1;
    }
};
