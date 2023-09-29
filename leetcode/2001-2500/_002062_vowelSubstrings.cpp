class Solution {
    const string vowels = "aeiou";
    
    // Assumes it will be called with all vowels only.
    bool hasAllVowels(const string& s, int start, int end) {
        unordered_set<char> vset;
        for (int i=start; i<=end; i++) {
            vset.insert(s[i]);
        }
        return (vset.size() == 5);
    }
    
    int countAllValid(const string& s, int start, int end) {
        int count=0;
        for (int i=start; i<=end; i++) {
            for (int j=i; j<=end; j++) {
                if (hasAllVowels(s, i, j)) {count++;}
            }
        }
        return count;
    }
public:
    // Brute force.
    int countVowelSubstrings(string word) {
        int w_ptr=0, count=0;
        while (w_ptr < word.size() && w_ptr != string::npos) {
            int pos_s = word.find_first_of(vowels, w_ptr);
            if (pos_s == string::npos) break;
            int pos_e = word.find_first_not_of(vowels, pos_s);
            count += countAllValid(word, pos_s, (pos_e == string::npos ? word.size()-1:pos_e-1));
            w_ptr = pos_e;
        }
        return count;
    }
};
