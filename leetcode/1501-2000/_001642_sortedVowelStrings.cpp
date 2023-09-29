class Solution {
public:
    // let cvs(n, l) denote the number of strings of length var n starting with vowel var l.
    // (l can only be 'a', 'e', 'i', 'o', 'u')
    // 
    // cvs(n, 'a') = cvs(n-1, 'a') + cvs(n-1, 'e') + cvs(n-1, 'i') + cvs(n-1, 'o') + cvs(n-1, 'u')
    // cvs(n, 'e') = cvs(n-1, 'e') + cvs(n-1, 'i') + cvs(n-1, 'o') + cvs(n-1, 'u')
    // cvs(n, 'i') = cvs(n-1, 'i') + cvs(n-1, 'o') + cvs(n-1, 'u')
    // cvs(n, 'o') = cvs(n-1, 'o') + cvs(n-1, 'u')
    // cvs(n, 'u') = cvs(n-1, 'u')
    
    string signature(int n, char letter) {
        return (std::to_string(n) + std::string(1, letter));
    }
    
    int countVowelStrings(int n) {
        unordered_map<string, int> cache;
        cache[signature(1, 'a')] = cache[signature(1, 'e')] =  cache[signature(1, 'i')] =  
            cache[signature(1, 'o')] = cache[signature(1, 'u')] = 1;
        
        string vowels = "aeiou";
        for (int ni=2; ni<=n; ni++) {
            for (int si=0; si<vowels.size(); si++) {
                string sig = signature(ni, vowels[si]);
                int val=0;
                switch(vowels[si]) {
                    case 'a':
                        val += cache[signature(ni-1, 'a')];  // continue
                    case 'e':
                        val += cache[signature(ni-1, 'e')];  // continue
                    case 'i':
                        val += cache[signature(ni-1, 'i')];  // continue
                    case 'o':
                        val += cache[signature(ni-1, 'o')];  // continue
                    case 'u':
                        val += cache[signature(ni-1, 'u')];
                }
                cache[sig] = val;
            }
        }
        
        return (cache[signature(n, 'a')] + cache[signature(n, 'e')] + cache[signature(n, 'i')] +
                cache[signature(n, 'o')] + cache[signature(n, 'u')]);
    }
};


