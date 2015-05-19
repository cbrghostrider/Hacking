class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n1cp=0, n1fp=0;
        while (n1fp < nums.size()) {
            if (nums[n1fp] != val) {
                n1cp++;
                n1fp++;
            } else {
                n1fp++;
                while (n1fp < nums.size() && nums[n1fp] != val) {
                    nums[n1cp++] = nums[n1fp++];
                }
            }
        }
        return n1cp;
    }
};
