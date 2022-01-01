class Solution {
    struct Info {
        int height=0;       // my height
        int num_between=0;  // num of people between me and my next greater on my right
    };
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        vector<Info> mono_stack;  // Monotonic stack magic, FTW!
        vector<int> ans;
        
        for (int i=heights.size()-1; i>=0; i--) {
            int my_between=0;
            int my_height=heights[i];
            while (!mono_stack.empty() && mono_stack.back().height < my_height) {
                my_between++;  // add the potential next greater guy                
                mono_stack.pop_back();
            }
            int my_ans = my_between;
            if (!mono_stack.empty()) {my_ans++;}
            ans.push_back(my_ans);
            mono_stack.push_back({my_height, my_between});
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
