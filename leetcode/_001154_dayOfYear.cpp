class Solution {
    bool isLeapYear() {
        bool div4 = (year % 4 == 0);
        bool div100 = (year % 100 == 0);
        bool div400 = (year % 400 == 0);
        bool exception = (div100 && !div400);
        return (div4 && !exception);
    }
    vector<int> month_days = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year=0;
    int month=0;
    int day=0;
public:
    int dayOfYear(string date) {
        year = std::stoi(date.substr(0, 4));
        month = std::stoi(date.substr(5, 2));
        day = std::stoi(date.substr(8, 2));
        int leap_day = (isLeapYear() && month >= 3 ? 1 : 0);
        int total = day + leap_day;
        for (int i=0; i<month; i++) {
            total += month_days[i];
        }
        return total;
    }
};
