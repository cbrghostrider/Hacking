class Solution {
public:
    bool checkIfPangram(string sentence) {
        unordered_set<char> chars;
        for (char ch : sentence) {chars.insert(ch);}
        return (chars.size() == 26);  // sentence only contains lowercase english, no spaces
    }
};
