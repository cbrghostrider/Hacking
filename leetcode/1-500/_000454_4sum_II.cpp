class Solution {
public:

    // O(n^2) time, O(n^2) space.
    // Accepted.
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> sum12, sum34;
        
        for (int i=0; i<nums1.size(); i++) {
            for (int j=0; j<nums2.size(); j++) {
                sum12[nums1[i] + nums2[j]]++;
            }
        }
        
        for (int i=0; i<nums3.size(); i++) {
            for (int j=0; j<nums4.size(); j++) {
                sum34[nums3[i] + nums4[j]]++;
            }
        }

        int count=0;
        for (const auto& kv : sum12) {
            count += kv.second * sum34[kv.first * -1];
        }
        return count;
    }

    
    // O(n^3) time, and O(n) space. 
    // TLE.
    int fourSumCount_TLE(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> set4;
        for (int n : nums4) {set4[n]++;}
        
        int count=0;
        for (int i=0; i<nums1.size(); i++) {
            for (int j=-0; j<nums2.size(); j++) {
                for (int k=0; k<nums3.size(); k++) {
                    int sum3 = nums1[i] + nums2[j] + nums3[k];
                    count += set4[-1*sum3];
                }
            }
        }
        return count;
    }
};
