// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    //counting-sort since we only have 3 colors
    void sortColors(vector<int>& nums) {
        int bin[3]; //for the 3 colors
        bin[0] = bin[1] = bin[2]=0;
        for (const int& num : nums) {bin[num]++;}
        
        for (int ind=0, bid=0; bid<3; bid++) {
            for (int cid=0; cid<bin[bid]; cid++) {
                nums[ind++] = bid;
            }
        }
    }
};
