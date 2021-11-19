class Solution {
    const string vowels = "aeiouAEIOU";
public:
    bool halvesAreAlike(string s) {
        string s1 = s.substr(0, s.size()/2);
        string s2 = s.substr(s.size()/2);
        
        auto countVowels = [this](const string& s) -> int {
            int count=0;
            for_each(s.begin(), s.end(), [&count, this](const char ch) {
                if (vowels.find_first_of(string(1, ch)) != string::npos) {count++;}
            });
            return count;
        };
        
        return (countVowels(s1) == countVowels(s2));
    }
};
