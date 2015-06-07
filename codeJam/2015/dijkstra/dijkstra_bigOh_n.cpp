// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

struct Quat {
  bool neg;
  char ch;
  Quat() : neg(false), ch('1') {}
  Quat(bool n, char c) : neg(n), ch(c) {}
};

bool operator==(const Quat& lhs, const Quat& rhs)
{
    return (lhs.neg == rhs.neg && lhs.ch == rhs.ch);
}

Quat qprod[4][4] = {{Quat(false, '1'), Quat(false, 'i'), Quat(false, 'j'), Quat(false, 'k')},
                    {Quat(false, 'i'), Quat(true, '1'),  Quat(false, 'k'), Quat(true, 'j')},
                    {Quat(false, 'j'), Quat(true, 'k'),  Quat(true, '1'),  Quat(false, 'i')},
                    {Quat(false, 'k'), Quat(false, 'j'), Quat(true, 'i'),  Quat(true, '1')}};

void readInput (std::vector<std::pair<unsigned int, std::string> >& retVal)
{
    unsigned long long numTests = 0;
    std::cin >> numTests; 

    for (unsigned long long i=0; i<numTests; i++) {
        unsigned long long x=0, l=0;
        std::string str;
        std::cin >> l >> x ;
        std::cin >> str ;
        retVal.push_back(std::make_pair(x, str));
    }
}

unsigned long long getIndex(const Quat& q)
{
    switch (q.ch) {
        case '1' : return 0; 
        case 'i' : return 1;
        case 'j' : return 2;
        case 'k' : return 3;
        default : assert(0);
    }
    assert(0);
}

Quat qMult (const Quat& q1, const Quat& q2)
{
    Quat tabMul = qprod[getIndex(q1)][getIndex(q2)];
    if (q1.neg == true) {
        tabMul.neg = ! (tabMul.neg);
    }
    if (q2.neg == true) {
        tabMul.neg = ! (tabMul.neg);
    }
    return tabMul;
}


void getS1EndIndices(const std::vector<Quat>& quats, std::vector<unsigned long long>& retVal)
{
    if (quats.size() < 3) {
        return;
    }

    unsigned long long ctr=0;
    Quat multiple(false, '1'); //initially +1 multiple
    Quat qi(false, 'i');

    for (auto it = quats.begin() ; it != quats.end() - 2; it++, ctr++) {
        const Quat& q = *it;
        multiple = qMult (multiple, q);
        if (multiple == qi) {
            retVal.push_back(ctr);
        }
    }
}

void getS3StartIndices(const std::vector<Quat>& quats, std::vector<unsigned long long>& retVal)
{
    if (quats.size() < 3) {
        return;
    }

    unsigned long long ctr = quats.size() - 1;
    Quat multiple(false, '1'); //initially +1 multiple
    Quat qk(false, 'k');

    for (auto it = quats.rbegin(); it != quats.rend() - 2; it++, ctr--) {
        const Quat& q = *it;
        multiple = qMult (q, multiple);
        if (multiple == qk) {
            retVal.push_back(ctr);
        }
    }
}

Quat wholeStringProduct(const std::vector<Quat>& quats)
{
    Quat retVal = std::accumulate(quats.begin(), quats.end(), Quat(false, '1'), qMult);
    return retVal;
}

bool checkTest (std::vector<Quat>& quats) 
{
    if (quats.size() < 3) {
        return false;
    }

    std::vector<unsigned long long> s1EndInds;
    std::vector<unsigned long long> s3StartInds;

    getS1EndIndices  (quats, s1EndInds);
    getS3StartIndices(quats, s3StartInds);

    if (s1EndInds.size() == 0 || s3StartInds.size() == 0) {
        return false;
    }

    std::sort(s1EndInds.begin(),   s1EndInds.end());
    std::sort(s3StartInds.begin(), s3StartInds.end());

    unsigned long long s1EarliestEnd = s1EndInds.front();
    unsigned long long s3LatestStart = s3StartInds.back();

    Quat wholeString = wholeStringProduct(quats);

    if ((s1EarliestEnd < s3LatestStart) && (wholeString == Quat(true, '1'))){
        return true;
    }

    return false;
}

int main()
{
    std::vector<std::pair<unsigned int, std::string> > tests;
    readInput(tests);
    unsigned long long ctr=1;
    for(auto it = tests.begin(); it != tests.end(); it++, ctr++) {
        unsigned int times = (*it).first;
        std::string& s = (*it).second;
        std::string str;
        for (unsigned int i=0; i<times; i++) {
            str.append(s);
        }

        std::vector<Quat> quats(str.size(), Quat());

        std::transform(str.begin(), str.end(), quats.begin(), [] (const char& ch) -> Quat {
            return Quat(false, ch);
        });

        assert(quats.size() == str.size());

        bool result = checkTest(quats);

        std::cout << "Case #" << ctr << ": " << (result ?  "YES" : "NO") << std::endl;
    }
    
}

