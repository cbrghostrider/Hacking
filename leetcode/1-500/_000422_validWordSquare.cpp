class Solution {
public:
    bool validWordSquare(vector<string>& words) {
        int ymax = words.size();
        int xmax = words[0].size();
        for (const string& word : words) {
            if (xmax < word.size()) {
                xmax = word.size();
            }
        }
        
        int max = (ymax > xmax) ? ymax : xmax;
        vector<vector<char>> letters(max, vector<char>(max, ' '));
        
        for (int i = 0; i<words.size(); i++) {
            const string& word = words[i];
            for (int w = 0; w<word.size(); w++) {
                letters[i][w] = word[w];
            }
        }
        
        for (int y = 0; y < ymax; y++) {
            for (int x = 0; x < xmax; x++) {
                if (letters[x][y] != letters[y][x]) return false;
            }
        }
        return true;
    }
};
