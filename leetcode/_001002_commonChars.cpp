class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        std::multiset<char> result;
        for (char c : words[0]) {result.insert(c);}
        
        for (string word : words) {
            std::multiset<char> result2, temp;
            for (char c : word) {temp.insert(c);}
            std::set_intersection(result.begin(), result.end(), temp.begin(), temp.end(), 
                                  std::inserter(result2, result2.begin()));
            result = result2;
            result2.clear();
        }
        
        vector<string> ans;
        for (char c : result) {
            ans.push_back(string(1, c));
        }
        return ans;
    }
};
