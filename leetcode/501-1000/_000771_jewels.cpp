class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        unordered_set<char> js;
        for (char ch : jewels) {js.insert(ch);}
        int count = 0;
        for (char ch : stones) {
            if (js.find(ch) != js.end()) count++;
        } 
        return count;
    }
};
