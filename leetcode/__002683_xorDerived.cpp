class Solution {

public:
    bool doesValidArrayExist(vector<int>& derived) {
        
        int xoor=0;
        for (int i=0; i<derived.size(); i++) {
            xoor ^= derived[i];
        }
        return xoor == 0;
    }
};
