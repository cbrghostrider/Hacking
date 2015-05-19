// Asked to assume that nums1 has enough space for (m+n)
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        std::copy(nums1.rbegin()+n, nums1.rend(), nums1.rbegin());
        int n1cp=0, n1p = n, n2p=0;
        while (n1p < (m+n) && n2p < n) {
            if (nums1[n1p] < nums2[n2p]) {
                nums1[n1cp++] = nums1[n1p++];
            } else {
                nums1[n1cp++] = nums2[n2p++];
            }
        }
        if (n2p < n) {
            std::copy(nums2.begin() + n2p, nums2.end(), nums1.begin() + n1cp);
        }
        if (n1p < n) {
            std::copy(nums1.begin() + n1p, nums1.end(), nums1.begin() + n1cp);
        }
    }
};
