class Solution {
    struct Info {
        unordered_map<int, int> steps_to_seq_len;
    };
public:
    // let las(i) be the longest arithmetic subsequence ending at index i
    // to compute las(i), we check all previous sequences ending at j < i, and check if nums[i] continues the sequence
    // we record the longest answer for las(i)
    // O(n^2) time, O(n^2) space.
    int longestArithSeqLength(vector<int>& nums) {
        vector<unordered_map<int, int>> las(nums.size(), {{}});
        
        // Base case.
        las[0] = {{0, 1}};
        int max_len = 1;
        
        for (int i=1; i<nums.size(); i++) {
            for (int j=i-1; j>=0; j--) {                
                int curr_step = nums[i] - nums[j];
                if (las[i][curr_step] == 0) {
                    las[i][curr_step] = std::max(las[j][curr_step] + 1, 2);
                } else {
                    las[i][curr_step] = std::max(las[i][curr_step], las[j][curr_step] + 1);
                }
                if (las[i][curr_step] > max_len) {
                    max_len = las[i][curr_step];
                }
            }
        }
        return max_len;
    }
};

