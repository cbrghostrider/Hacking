class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        
        vector<int> result;
        int prev = 0, p2 = 0;
        for (int p1=0; p1<nums1.size(); p1++) {
            int find = nums1[p1];
            if (p1 != 0 && find == prev) {
                continue;
            } else {
                prev = find;
            }
            
            while (p2 < nums2.size()) {
                int check = nums2[p2];
                
                if (check == find) {
                    result.push_back(find);
                    p2++;
                    break;
                } else if (check < find) {
                    p2++;
                } else {
                    break;
                }
            }
        }
        return result;
    }
};
