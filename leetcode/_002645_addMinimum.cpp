class Solution {
public:
    int addMinimum(string word) {        
        int adds=0;
        char last='c';
        unordered_map<char, char> next;
        next['a'] = 'b'; next['b'] = 'c'; next['c'] = 'a';        
        for (int i=0; i<word.size();) {
            if (word[i] == next[last]) {
                last = word[i++];
            } else {
                adds++;
                last = next[last];
            }
        }
        if (last == 'a') {adds += 2;}
        else if (last == 'b') {adds++;}
        return adds;
    }
};
