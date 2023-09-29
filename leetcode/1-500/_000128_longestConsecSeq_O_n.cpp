class Solution {
    struct Info {
        int my_index=-1;
        int prev_index=-1;
        int next_index=-1;
        bool examined = false;
    };
    // (val -> index)
    unordered_map<int, int> location;
    vector<Info> infos;
    
    int examine(int ind, bool go_forward=true) {
        int len=0;
        
        // returns successor index, accounting for go_forward (moves front or back)
        // returns -1 if no succ
        auto succ = [this, go_forward](int ind) -> int {
            return (go_forward ? infos[ind].next_index : infos[ind].prev_index);
        };
        int nxt=-1;
        while ((nxt = succ(ind)) != -1) {
            infos[nxt].examined = true;
            ind = nxt;
            len++;
        }
        return len;
    }
    
public:
    // O(n) time, O(n) space.
    //
    // Each element is only encountered twice in the main work loop.
    // The first time, when we iterate through the loop.
    // The second time, when we "examine" it.
    // (Or vice versa in order, it may be examined first as part of the chain).
    // Regardless, across all elements, only 2n amount of work is performed.
    int longestConsecutive(vector<int>& nums) {    
        infos = vector<Info>(nums.size(), Info());
        
        for (int i=0; i<nums.size(); i++) {
            location[nums[i]] = i;
            Info& my_info = infos[i];
            my_info.my_index = i;
            if (location.find(nums[i]-1) != location.end()) {
                my_info.prev_index = location[nums[i]-1];
                infos[location[nums[i]-1]].next_index = i;
            }
            if (location.find(nums[i]+1) != location.end()) {
                my_info.next_index = location[nums[i]+1];
                infos[location[nums[i]+1]].prev_index = i;
            }
        }
        
	// Main work loop.
        int longest=0;
        for (int i=0; i<nums.size(); i++) {
            if (infos[i].examined) continue;
            infos[i].examined = true;
            int len_fwd  = examine(i, /*forward=*/true);
            int len_back = examine(i, /*forward=*/false);
            int len = 1 + len_fwd + len_back;
            longest = std::max(len, longest);
        }
        return longest;
    }
};
