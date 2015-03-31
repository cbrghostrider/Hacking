//Author ssjoshi

#ifndef BERLIN_CLOCK_H_
 #define BERLIN_CLOCK_H_

#include <array>
#include <iostream>
#include <cstdio>
#include <utility>
#include <string>

using std::ostream;
using std::array;
using std::pair;
using std::string;

enum LampColor {
    LampYellow,
    LampRed
};

class BerlinSeconds {
public: 
    BerlinSeconds(unsigned int secs);    
    ~BerlinSeconds();

    friend ostream& operator<<(ostream&, BerlinSeconds& bs);
private:
    typedef array<pair<const LampColor, bool>, 1>  BerlinSec;
    BerlinSec sec_repr;
};

class BerlinHours {
public: 
    BerlinHours(unsigned int hrs);    
    ~BerlinHours();

    friend ostream& operator<<(ostream&, BerlinHours& bh);
private:
    typedef array<pair<const LampColor, bool>, 4>  BerlinHrs;
    BerlinHrs hrs_hi_repr;
    BerlinHrs hrs_lo_repr;
};

class BerlinMinutes {
public: 
    BerlinMinutes(unsigned int mins);    
    ~BerlinMinutes();

    friend ostream& operator<<(ostream&, BerlinMinutes& bm);
private:
    typedef array<pair<const LampColor, bool>, 11> BerlinMinHi;
    typedef array<pair<const LampColor, bool>, 4>  BerlinMinLo;

    BerlinMinHi min_hi_repr;
    BerlinMinLo min_lo_repr;
};

class BerlinClock {
public:
    BerlinClock(unsigned int hrs, unsigned int mins, unsigned int secs);
    ~BerlinClock();

    friend ostream& operator<<(ostream& os, BerlinClock& bc);
private:
    BerlinHours bh;
    BerlinMinutes bm;
    BerlinSeconds bs;
    

};

#endif /* BERLIN_CLOCK_H_ */
