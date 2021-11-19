class Solution {
    std::unordered_map<string, int> month_to_num = {
        {"Jan", 1}, {"Feb", 2},  {"Mar", 3},  {"Apr", 4},
        {"May", 5}, {"Jun", 6},  {"Jul", 7},  {"Aug", 8},
        {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
    };
public:
    string reformatDate(string date) {
        string ans;
        int pos = date.find_first_not_of("0123456789");
        string day = date.substr(0, pos);
        if (day.size() == 1) {day = "0" + day;}
        
        pos = date.find_first_of(" ");
        string month = std::to_string(month_to_num[date.substr(pos+1, 3)]);
        if (month.size() == 1) {month = "0" + month;}
        
        string year = date.substr(date.size()-4, 4);
        return (year + "-" + month + "-" + day);
    }
};
