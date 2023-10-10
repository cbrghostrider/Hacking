class Solution {
    struct NumInfo {
        string num;
        int pos=0;  // The original position in the nums array.
    };
    vector<NumInfo> infos;
    int MSB_POS=0;

    // Outer index: trim_size - 1    
    // Values: The sorted order for those keys.
    vector<vector<int>> answers;

    // precompute will repeatedly apply radix sort from LSB to the MSB.
    void precompute() {
        answers = vector<vector<int>>(infos[0].num.size(), vector<int>());
	// Note that we have to "flip" the loop here, because index 0 stores the string MSB.
        for (int pos=MSB_POS; pos>=0; pos--) {
            // Radix sort on position "pos".
            std::stable_sort(infos.begin(), infos.end(), [this, pos](const NumInfo& lhs, const NumInfo& rhs) -> bool {                
                return lhs.num[pos] < rhs.num[pos];
            });

            // store precomputed information.                        
            for (const auto& info : infos) {                
                answers[MSB_POS - pos].push_back(info.pos);
            }            
        }
    }
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        MSB_POS = nums[0].size()-1;

        infos.reserve(nums.size());
        for (int i=0; i<nums.size(); i++) {
            infos.push_back({nums[i], i});
        }

        precompute();

        vector<int> ret;
        ret.reserve(queries.size());
        for (const auto& query : queries) {
            int trim = query[1] - 1;
            int k = query[0] - 1;
            ret.push_back(answers[trim][k]);
        }
        return ret;
    }
};
