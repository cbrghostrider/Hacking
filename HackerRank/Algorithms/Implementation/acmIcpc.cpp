// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using std::string;
using std::vector;

typedef unsigned long long ClassInfo;

class PersonInfo {
public:
    PersonInfo(int classsize);
    void readPerson();
    int countTopics();
    PersonInfo& operator=(const PersonInfo& rhs);
    friend PersonInfo operator|(const PersonInfo& lhs, const PersonInfo& rhs);
private:
    const int CLASSSIZE;
    const int VECTSIZE;
    vector<ClassInfo> topics;
};

PersonInfo::PersonInfo(int classsize)
: CLASSSIZE(classsize), VECTSIZE((classsize/(8* sizeof (ClassInfo))) + ((classsize % (8*sizeof(ClassInfo))) ? 1 : 0)), topics(VECTSIZE, 0) {
}

PersonInfo& PersonInfo::operator=(const PersonInfo& rhs) {
    topics = rhs.topics;
    return (*this);
}

void PersonInfo::readPerson() {
    string str; std::cin >> str;
    for (int cind = 0; cind<VECTSIZE; cind++) {
        ClassInfo mask = 0x1;
        for (int i=0; i<(8*sizeof(ClassInfo)); i++) {
            int index = cind*(8*sizeof (ClassInfo)) + i;
            if (index >= str.length()) return;
            if (str[index] == '1') {
                topics[cind] |= mask;
            }
            mask <<= 1;
        }
    }
}

PersonInfo operator|(const PersonInfo& lhs, const PersonInfo& rhs) {
    PersonInfo retval(lhs.CLASSSIZE);
    for (int cind = 0; cind < lhs.VECTSIZE; cind++) {
        ClassInfo acc = 0;
        ClassInfo mask = 1;
        for (int i=0; i<(8*sizeof(ClassInfo)); i++) {
            acc |= ((lhs.topics[cind] & mask) | (rhs.topics[cind] & mask));
            mask <<= 1;
        }
        retval.topics[cind] = acc;
    }
    return retval;
}

int PersonInfo::countTopics() {
    int retval = 0;
    for (int cind = 0; cind<VECTSIZE; cind++) {
        ClassInfo mask = 0x1;
        for (int i=0; i<(8*sizeof(ClassInfo)); i++) {
            if (topics[cind] & mask) {
                retval++;
            }
            mask <<= 1;
        }
    }
    return retval;
}

class AcmIcpc {
public:
    AcmIcpc(int numpersons, int classsize);
    void computeOutput();
private:
    void readInput();
    const int CSIZE;
    vector<PersonInfo> persons;
};

AcmIcpc::AcmIcpc(int numpersons, int classsize)
: CSIZE(classsize), persons() {
    persons.reserve(numpersons);
    for (int i=0; i<numpersons; i++) {
        PersonInfo person(classsize);
        person.readPerson();
        persons.push_back(person);
    }
}

void AcmIcpc::computeOutput() {
    vector<int> counts;
    int max = 0;
    for (int i=0; i<persons.size(); i++) {
        for (int j=i+1; j<persons.size(); j++) {
            PersonInfo combined(CSIZE); 
            combined = persons[i] | persons[j];
            int mycount = combined.countTopics();
            counts.push_back(mycount);
            if (mycount > max) {
                max = mycount;
            }
        }
    }
    int nummax = 0;
    for (int i=0; i<counts.size(); i++) {
        if (counts[i] == max) {
            nummax++;
        }
    }
    std::cout << max << std::endl;
    std::cout << nummax << std::endl;
}

int main() {
    int n, m; std::cin >> n >> m;
    AcmIcpc acm(n, m);
    acm.computeOutput();
}

