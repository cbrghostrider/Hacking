/*
 * berlin-clock-tests.cpp
 *
 *  Created on: Oct 24, 2014
 *      Author: rmhyman
 */
#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include "berlin-clock.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::string;

vector<string> GetBerlinClockOut(BerlinClock& bc)
{
    std::ostringstream os;
    os << bc;
    std::istringstream is(os.str());
    std::string myline;
    vector<string> retval;
    while (std::getline(is, myline)) {
        if (!myline.empty()) { 
            retval.push_back(myline);
        }
    }
    return retval;
}

TEST(BerlinClock, sec_00) {
    BerlinClock bc(0, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("Y"), out[0]);
}

TEST(BerlinClock, sec_01) {
    BerlinClock bc(0, 0, 1);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("O"), out[0]);
}

TEST(BerlinClock, sec_02) {
    BerlinClock bc(0, 0, 2);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("Y"), out[0]);
}

TEST(BerlinClock, hrs_00) {
    BerlinClock bc(0, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("OOOO"), out[1]);
}

TEST(BerlinClock, hrs_04) {
    BerlinClock bc(4, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("OOOO"), out[1]);
    EXPECT_EQ(string("RRRR"), out[2]);
}

TEST(BerlinClock, hrs_05) {
    BerlinClock bc(5, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("ROOO"), out[1]);
    EXPECT_EQ(string("OOOO"), out[2]);
}

TEST(BerlinClock, hrs_06) {
    BerlinClock bc(6, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("ROOO"), out[1]);
    EXPECT_EQ(string("ROOO"), out[2]);
}

TEST(BerlinClock, hrs_09) {
    BerlinClock bc(9, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("ROOO"), out[1]);
    EXPECT_EQ(string("RRRR"), out[2]);
}

TEST(BerlinClock, hrs_10) {
    BerlinClock bc(10, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RROO"), out[1]);
    EXPECT_EQ(string("OOOO"), out[2]);
}

TEST(BerlinClock, hrs_1) {
    BerlinClock bc(11, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RROO"), out[1]);
    EXPECT_EQ(string("ROOO"), out[2]);
}

TEST(BerlinClock, hrs_14) {
    BerlinClock bc(14, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RROO"), out[1]);
    EXPECT_EQ(string("RRRR"), out[2]);
}

TEST(BerlinClock, hrs_15) {
    BerlinClock bc(15, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RRRO"), out[1]);
    EXPECT_EQ(string("OOOO"), out[2]);
}

TEST(BerlinClock, hrs_16) {
    BerlinClock bc(16, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RRRO"), out[1]);
    EXPECT_EQ(string("ROOO"), out[2]);
}

TEST(BerlinClock, hrs_19) {
    BerlinClock bc(19, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RRRO"), out[1]);
    EXPECT_EQ(string("RRRR"), out[2]);
}

TEST(BerlinClock, hrs_20) {
    BerlinClock bc(20, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RRRR"), out[1]);
    EXPECT_EQ(string("OOOO"), out[2]);
}

TEST(BerlinClock, hrs_21) {
    BerlinClock bc(21, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RRRR"), out[1]);
    EXPECT_EQ(string("ROOO"), out[2]);
}

TEST(BerlinClock, hrs_22) {
    BerlinClock bc(22, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RRRR"), out[1]);
    EXPECT_EQ(string("RROO"), out[2]);
}

TEST(BerlinClock, hrs_23) {
    BerlinClock bc(23, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RRRR"), out[1]);
    EXPECT_EQ(string("RRRO"), out[2]);
}

TEST(BerlinClock, hrs_24) {
    BerlinClock bc(24, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("RRRR"), out[1]);
    EXPECT_EQ(string("RRRR"), out[2]);
}

TEST(BerlinClock, mins_04) {
    BerlinClock bc(0, 4, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("OOOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, mins_05) {
    BerlinClock bc(0, 5, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YOOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}

TEST(BerlinClock, mins_06) {
    BerlinClock bc(0, 6, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YOOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("YOOO"), out[4]);
}

TEST(BerlinClock, mins_09) {
    BerlinClock bc(0, 9, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YOOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, mins_10) {
    BerlinClock bc(0, 10, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}

TEST(BerlinClock, mins_11) {
    BerlinClock bc(0, 11, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("YOOO"), out[4]);
}

TEST(BerlinClock, mins_14) {
    BerlinClock bc(0, 14, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, mins_15) {
    BerlinClock bc(0, 15, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYROOOOOOOO"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}

TEST(BerlinClock, mins_16) {
    BerlinClock bc(0, 16, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYROOOOOOOO"), out[3]);
    EXPECT_EQ(string("YOOO"), out[4]);
}

TEST(BerlinClock, mins_19) {
    BerlinClock bc(0, 19, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYROOOOOOOO"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, mins_20) {
    BerlinClock bc(0, 20, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYOOOOOOO"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}

TEST(BerlinClock, mins_21) {
    BerlinClock bc(0, 21, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYOOOOOOO"), out[3]);
    EXPECT_EQ(string("YOOO"), out[4]);
}

TEST(BerlinClock, mins_24) {
    BerlinClock bc(0, 24, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYOOOOOOO"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, mins_25) {
    BerlinClock bc(0, 25, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYOOOOOO"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}

TEST(BerlinClock, mins_26) {
    BerlinClock bc(0, 26, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYOOOOOO"), out[3]);
    EXPECT_EQ(string("YOOO"), out[4]);
}


TEST(BerlinClock, mins_29) {
    BerlinClock bc(0, 29, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYOOOOOO"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, mins_30) {
    BerlinClock bc(0, 30, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYROOOOO"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}

TEST(BerlinClock, mins_31) {
    BerlinClock bc(0, 31, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYROOOOO"), out[3]);
    EXPECT_EQ(string("YOOO"), out[4]);
}

TEST(BerlinClock, mins_54) {
    BerlinClock bc(0, 54, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYRYYRYO"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, mins_55) {
    BerlinClock bc(0, 55, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYRYYRYY"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}

TEST(BerlinClock, mins_56) {
    BerlinClock bc(0, 56, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYRYYRYY"), out[3]);
    EXPECT_EQ(string("YOOO"), out[4]);
}

TEST(BerlinClock, mins_57) {
    BerlinClock bc(0, 57, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYRYYRYY"), out[3]);
    EXPECT_EQ(string("YYOO"), out[4]);
}

TEST(BerlinClock, mins_58) {
    BerlinClock bc(0, 58, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYRYYRYY"), out[3]);
    EXPECT_EQ(string("YYYO"), out[4]);
}

TEST(BerlinClock, mins_59) {
    BerlinClock bc(0, 59, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("YYRYYRYYRYY"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, mins_60) {
    BerlinClock bc(0, 60, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("OOOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}

TEST(BerlinClock, full_clock_t0) {
    BerlinClock bc(13, 17, 1);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("O"), out[0]);
    EXPECT_EQ(string("RROO"), out[1]);
    EXPECT_EQ(string("RRRO"), out[2]);
    EXPECT_EQ(string("YYROOOOOOOO"), out[3]);
    EXPECT_EQ(string("YYOO"), out[4]);
}

TEST(BerlinClock, full_clock_t1) {
    BerlinClock bc(23, 59, 59);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("O"), out[0]);
    EXPECT_EQ(string("RRRR"), out[1]);
    EXPECT_EQ(string("RRRO"), out[2]);
    EXPECT_EQ(string("YYRYYRYYRYY"), out[3]);
    EXPECT_EQ(string("YYYY"), out[4]);
}

TEST(BerlinClock, full_clock_t2) {
    BerlinClock bc(24, 0, 0);
    vector<string> out = GetBerlinClockOut(bc);
    EXPECT_EQ(string("Y"), out[0]);
    EXPECT_EQ(string("RRRR"), out[1]);
    EXPECT_EQ(string("RRRR"), out[2]);
    EXPECT_EQ(string("OOOOOOOOOOO"), out[3]);
    EXPECT_EQ(string("OOOO"), out[4]);
}





