class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        vector<int> orig(encoded.size() + 1, 0);
        orig[0] = first;
        for (int i=0; i<encoded.size(); i++) {
            orig[i+1] = (orig[i] ^ encoded[i]);
        }
        return orig;
    }
};
