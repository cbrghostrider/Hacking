class Solution {
    class Date {
      public:
        Date(const string& d) : 
          date(d), year(std::stoi(date.substr(0, 4))), 
          month(std::stoi(date.substr(5, 2))), day(std::stoi(date.substr(8, 2))) 
          {}
        
        bool isLeapYear() const {
            bool div4 = (year % 4 == 0);
            bool div100 = (year % 100 == 0);
            bool div400 = (year % 400 == 0);
            bool exception = (div100 && !div400);
            return (div4 && !exception);
        }
        bool operator>(const Date& rhs) const {
            if (year != rhs.Year()) return (year > rhs.Year());
            if (month != rhs.Month()) return (month > rhs.Month());
            return (day > rhs.Day());
        }
        int daysSince1971() const {
            int count = 0;
            
            // For current year.
            for (int i=0; i<month; i++) {
                count += month_days[i];
            }
            count += (isLeapYear() && month >= 3 ? 1 : 0);
            count += day;
            
            // For past years.
            for (int i=1971; i<year; i++) {
                count += 365;
                Date date = std::to_string(i) + "-01-01";
                if (date.isLeapYear()) count += 1;
            }
            return count;
        }
        int operator-(const Date& rhs) const {
            if (rhs.operator>(*this)) return (rhs - *this);
            return (daysSince1971() - rhs.daysSince1971());
        }
        int Year() const {return year;}
        int Month() const {return month;}
        int Day() const {return day;}
      private:
        vector<int> month_days = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        const string date;
        const int year =0;
        const int month =0;
        const int day =0;
    };
public:
    int daysBetweenDates(string date1, string date2) {
        Date d1(date1), d2(date2);
        if (d1 > d2) return (d1 - d2);
        return (d2 - d1);
    }
};
