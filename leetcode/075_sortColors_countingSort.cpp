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
