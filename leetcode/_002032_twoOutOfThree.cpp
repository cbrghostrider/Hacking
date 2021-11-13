class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
        vector<int> ans;
        std::set<int> vals1(nums1.begin(), nums1.end());
        std::set<int> vals2(nums2.begin(), nums2.end());
        std::set<int> vals3(nums3.begin(), nums3.end());
        std::set<int> inter1, inter2, inter3, union1;
        std::set_intersection(vals1.begin(), vals1.end(), vals2.begin(), vals2.end(), 
                              std::inserter(inter1, inter1.begin()));
        std::set_intersection(vals2.begin(), vals2.end(), vals3.begin(), vals3.end(), 
                              std::inserter(inter2, inter2.begin()));
        std::set_intersection(vals1.begin(), vals1.end(), vals3.begin(), vals3.end(), 
                              std::inserter(inter3, inter3.begin()));
        std::set_union(inter1.begin(), inter1.end(), inter2.begin(), inter2.end(),
                      std::inserter(union1, union1.begin()));
        std::set_union(inter3.begin(), inter3.end(), union1.begin(), union1.end(),
                      std::back_inserter(ans));
        return ans;
    }
};
