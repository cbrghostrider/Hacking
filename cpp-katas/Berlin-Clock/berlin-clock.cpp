//Author ssjoshi

#include "berlin-clock.h"
#define COUNTS_PER_LAMP (5) // 5 ticks of something (mins or hrs) causes one lamp in hi low to be lit

static void CondLightLamp(pair<const LampColor, bool>& lamp, unsigned int& lit_so_far, const unsigned int total_lit)
{
    if (lit_so_far < total_lit) {
        lamp.second = true;
        lit_so_far++;
    }
}

static string ShowLight(const pair<const LampColor, bool>& lamp)
{
    if (lamp.second) {
        return ((lamp.first == LampRed) ? string("R"): string("Y"));
    }
    return string("O");
}

BerlinClock::BerlinClock(unsigned int hrs, unsigned int mins, unsigned int secs) 
: bh(hrs), bm(mins), bs(secs)
{
}

BerlinClock::~BerlinClock() 
{
}

ostream& operator<<(ostream& os, BerlinClock& bc)
{
    os << bc.bs << bc.bh << bc.bm << std::endl;
    return os;
}

BerlinSeconds::BerlinSeconds(unsigned int secs)
: sec_repr {{{LampYellow, false}}}
{
    secs = secs % 60;

    if ((secs % 2) == 0) {
        sec_repr[0].second = true;
    }
}

BerlinSeconds::~BerlinSeconds()
{
}

ostream& operator<<(ostream& os, BerlinSeconds& bs)
{
    os << ShowLight(bs.sec_repr[0]) << std::endl;
    return os;
}

BerlinMinutes::BerlinMinutes(unsigned int mins)
: min_hi_repr {{{LampYellow, false}, {LampYellow, false}, {LampRed, false}, 
                {LampYellow, false}, {LampYellow, false}, {LampRed, false},
                {LampYellow, false}, {LampYellow, false}, {LampRed, false},
                {LampYellow, false}, {LampYellow, false}}},
  min_lo_repr {{{LampYellow, false}, {LampYellow, false}, {LampYellow, false}, {LampYellow, false}}}
{
    mins = mins % 60;

    unsigned int min_hi_lit = mins / COUNTS_PER_LAMP;
    unsigned int min_lo_lit = mins % COUNTS_PER_LAMP;

    unsigned int lamps_lit = 0;
    for (pair<const LampColor, bool>& lamp : min_hi_repr) {
        CondLightLamp(lamp, lamps_lit, min_hi_lit);
    }
    lamps_lit = 0;
    for (pair<const LampColor, bool>& lamp : min_lo_repr) {
        CondLightLamp(lamp, lamps_lit, min_lo_lit);
    }
}

BerlinMinutes::~BerlinMinutes()
{
}

ostream& operator<<(ostream& os, BerlinMinutes& bm)
{
    for (pair<const LampColor, bool>& lamp : bm.min_hi_repr) {
        os << ShowLight(lamp);
    }
    os << std::endl;
    for (pair<const LampColor, bool>& lamp : bm.min_lo_repr) {
        os << ShowLight(lamp);
    }
    os << std::endl;
    return os;
}

BerlinHours::BerlinHours(unsigned int hrs)
: hrs_hi_repr{{{LampRed, false}, {LampRed, false}, {LampRed, false}, {LampRed, false}}},
  hrs_lo_repr{{{LampRed, false}, {LampRed, false}, {LampRed, false}, {LampRed, false}}}
{
    hrs = hrs % 25; //note: not 24 but 25, since the clock can count 24 full hrs and more mins and secs

    unsigned int hrs_hi_lit = hrs / COUNTS_PER_LAMP;
    unsigned int hrs_lo_lit = hrs % COUNTS_PER_LAMP;

    unsigned int lamps_lit = 0;
    for (pair<const LampColor, bool>& lamp : hrs_hi_repr) {
        CondLightLamp(lamp, lamps_lit, hrs_hi_lit);
    }
    lamps_lit = 0;
    for (pair<const LampColor, bool>& lamp : hrs_lo_repr) {
        CondLightLamp(lamp, lamps_lit, hrs_lo_lit);
    }
}

BerlinHours::~BerlinHours()
{
}

ostream& operator<<(ostream& os, BerlinHours& bh)
{
    for (pair<const LampColor, bool>& lamp : bh.hrs_hi_repr) {
        os << ShowLight(lamp);
    }
    os << std::endl;
    for (pair<const LampColor, bool>& lamp : bh.hrs_lo_repr) {
        os << ShowLight(lamp);
    }
    os << std::endl;
    return os;
}




