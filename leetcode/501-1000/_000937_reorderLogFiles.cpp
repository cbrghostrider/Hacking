class Solution {
    struct Record {
        string identifier;
        string content;
    };
public:
    
    // O(n * s) time, O(n * s) space.
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<Record> letter_logs;
        vector<string> digit_logs;
        for (string log : logs) {
            size_t id_end = log.find_first_of(" ");  // guaranteed to exist (not npos)
            string id = log.substr(0, id_end);
            string content = log.substr(id_end);
            
            const string digits = " 0123456789";
            bool is_digit_log = (content.find_first_not_of(digits) == string::npos);
            if (is_digit_log) {
                digit_logs.push_back(id + content);
            } else {
                letter_logs.push_back({id, content});
            }
        }
        
        std::sort(letter_logs.begin(), letter_logs.end(), [](const Record& left, const Record& right) -> bool {
            if (left.content == right.content) {
                return left.identifier < right.identifier;
            }
            return left.content < right.content;
        });
        
        vector<string> ans;
        for (const Record& r : letter_logs) {ans.push_back(r.identifier + r.content);}
        ans.insert(ans.end(), digit_logs.begin(), digit_logs.end());
        return ans;
    }
};
