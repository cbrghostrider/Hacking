class Solution {
    class ParaProcessor {
      public:
        ParaProcessor(const string& s) : str(s) {
            for (char ch='a'; ch<='z'; ch++) all_letters.push_back(ch);
            for (char ch='A'; ch<='Z'; ch++) all_letters.push_back(ch);
        }
        
        bool hasNext() {
            if (s_ptr >= str.size() || s_ptr == string::npos) return false;
            if (str.find_first_of(all_letters, s_ptr) == string::npos) return false;
            return true;
        }
        
        string next() {
            if (!hasNext()) return "";
            int pos_start = str.find_first_of(all_letters, s_ptr);
            int pos_end = str.find_first_not_of(all_letters, pos_start);
            int len = (pos_end == string::npos ? str.size()-pos_start : pos_end-pos_start);
            s_ptr = pos_end;
            return str.substr(pos_start, len);
        }
        
      private:
        string str;
        string all_letters;
        int s_ptr = 0;
    };
    
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        std::unordered_set<string> bwords;
        for (const string& word : banned) bwords.insert(word);
        
        unordered_map<string, int> unbanned;
        string ret;
        int ret_count = std::numeric_limits<int>::min();
        ParaProcessor processor(paragraph);
        while (processor.hasNext()) {
            string word = processor.next();
            std::for_each(word.begin(), word.end(), [](char& ch) {
                ch = std::tolower(ch);
            });
            if (bwords.find(word) != bwords.end()) continue;
            unbanned[word]++;
            if (unbanned[word] > ret_count) {
                ret = word;
                ret_count = unbanned[word];
            }
        }
        return ret;
    }
};
