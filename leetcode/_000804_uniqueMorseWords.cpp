class Solution {
    vector<string> morse = {".-","-...","-.-.","-..",".","..-.","--.","....",
	    "..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...",
	    "-","..-","...-",".--","-..-","-.--","--.."};
    std::unordered_set<string> transformations;
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        for (const string& word : words) {
            string xf;
            for (char c : word) {
                xf += morse[std::tolower(c)-'a'];
            }
            transformations.insert(xf);
        }
        return transformations.size();
    }
};
