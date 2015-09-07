// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

typedef int Day;
typedef int Month;
typedef int Year;

vector<Day> monthDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

typedef unsigned int BigDate;
vector<BigDate> friday13;

BigDate convertToBigDate(Day day, Month month, Year year) {
    return (year*10000 + month*100 + day);
}

bool isLeapYear(Year year) {
    bool leap = ((year % 4) == 0);
    if ((year % 100 == 0) && (year % 400 != 0)) leap = false;
    return leap;
}

//if last day of a month is saturday, next month has friday the 13th
//Note: 0 denotes saturday
void populateFriday13() {
    Day day = 31;
    Month month = 3;
    Year year = 1900;
    int dayOfWeek = 0;

    while (day <= 31 && month <= 12 && year <= 9999) {
        if (dayOfWeek == 0) {
            Year bdyear   = (month == 12) ? year + 1 : year;
            Month bdmonth = (month == 12) ? 1 : month+1;
            Day bdday = 13;
            friday13.push_back(convertToBigDate(bdday, bdmonth, bdyear));
        }

        //compute end of next month
        if (month == 12) {
            year += 1;
            month = 1;
        } else {
            month++;
        }

        day = monthDays[month-1] + ((isLeapYear(year) && month == 2) ? 1 : 0);
        dayOfWeek = (dayOfWeek + (day % 7)) % 7;
    }
}

int numFriday13(Day day, Month month, Year year, bool& thisF13) {
    int retval = 0;
    BigDate target = convertToBigDate(day, month, year);
    for (const BigDate& bd : friday13) {
        if (bd < target) {
            retval++;
        } else if (bd == target) {
            retval++;
            thisF13 = true;
        } else {
            break;
        }
    }
    return retval;
}

int main() {
    populateFriday13();

    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        Day df, dt; Month mf, mt; Year yf, yt;
        std::cin >> df >> mf >> yf >> dt >> mt >> yt;
        bool fromf13 = false, tof13 = false;
        int numf13f = numFriday13(df, mf, yf, fromf13);
        int numf13t = numFriday13(dt, mt, yt, tof13);
        int numf13 = numf13t - numf13f + (fromf13 ? 1 : 0);
        std::cout << numf13 << std::endl;
    }
}
