// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// This problem is driving me NUTS! 
// I'm trying to solve this in O(n), and currently passing 9/17, the rest are WA.
//
// Here is the main issue with the problem:
//
// Initially the problem seems to be analogous to the merge step of merge sort, 
// sadly that is not the case. This is because the case where the two strings have
// equal chars, we need to look ahead (possibly quite a bit) before picking the right one
//
// e.g. (AAABBBBBC) and (AAABBBBBD) in this case, we need to look ahead until we notice a difference (c vs d)
// Unfortunately this makes the algorithm O(n^2)
//
// My Solution in O(n): 
// Assume s1p points to current location in str1, and s2p for str2.
// 
// This solution exploits what I call *speculative execution in software*. 
// e.g. in the above case, we will speculatively pick str1, and go ahead with the merging.
// (we will also note down some bookkeeping information, e.g. the positions where we first started
// our speculation as s1eqint and s2eqind. these are the indices of the first A in both strings)
//
// When we finally reach C vs D, we can check whether our speculation was correct. If so, we keep going
// as if nothing happened. If it was wrong, we can *switch* pointers to make s1p = s1eqind, and s2p = s2eqind + deltaTraveled
// This allows the whole algorithm to now finish in O(n)
//
// Of course, this was easier said than done. In particular, I found the details of the speculation very tricky to implement. 
// I have provided comments in the code below, to show the various cases, e.g.
            //      |
            // ->CABCCCC
            // ->CABAAAA
            //   |  *
// Here The starting Cs of both are s1eqind and s2eqind (pointed by ->)
// s2p remained at starting C, while s1p went ahead executing speculatively (denoted by |)
// In the above example, we noticed later on, that our speculation was wrong, so we will
// switch s1p to point to starting C, and s2p to point to the A (marked by *)
// Hope that makes sense.
//
// Unfortunately there is some bug somewhere, which causes 1 test pair from each of the tests from 10 onwards to fail.
// If you can get through the convoluted code below, and spot and fix the bug, PLEASE shoot me an email! :-)
//

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

using std::string;
using std::vector;

//s1p is the same as s2p
// how does s1p compare against s2future?
void processStateEqual(string& ret, const string& str1, const string& str2, int& s1p, int& s2p, int& s1eqind, int& s2eqind, bool& stateequal) {
    int delta = s1p - s1eqind;
    int s2future = s2p + delta;
    if (s2future < str2.length()) {
        if (str1[s1p] > str2[s2future]) { //made a bad decision earlier
            //    |
            // CABCCCC
            // CABAAAA
            // |
            s2p = s2future;
            s1p = s1eqind;
            stateequal = false;
        } else if (str1[s1p] < str2[s2future]) { //previous call was correct
            //    |
            // CABCCCC
            // CABDDDD
            // |
            stateequal = false; 
        } else { //same
            //    |
            // CABCCCC
            // CABCCCC
            // |
            ret.push_back(str1[s1p++]); //choose str1 speculatively
        }
    }  else {
        //    |
        // CABCCCC
        // CAB
        // |
        stateequal = false;
    }
}

// s1p is lesser than s2p
// how does s1p compare to s2future?
void processStateLesser(string& ret, const string& str1, const string& str2, int& s1p, int& s2p, int& s1eqind, int& s2eqind, bool& stateequal) {
    int delta = s1p - s1eqind;
    int s2future = s2p + delta;
    if (s2future < str2.length()) {
        if (str1[s1p] > str2[s2future]) { //made a bad decision earlier
            //    |
            // CABBBBB
            // CABABBB
            // |
            s2p = s2future;
            s1p = s1eqind;
            stateequal = false;
        } else if (str1[s1p] < str2[s2future]) { //previous call was correct
            //    |
            // CABACCC
            // CABDDDD
            // |
            stateequal = false;
        } else { //same
            //    |
            // CABACCC
            // CABADDD
            // |
            ret.push_back(str1[s1p++]); 
        }
    } else {
        //    |
        // CABACCC
        // CAB
        // |
        stateequal = false;
    }
}

// s1p is greater than s2p
// how does s2p compare to s2future?
void processStateGreater(string& ret, const string& str1, const string& str2, int& s1p, int& s2p, int& s1eqind, int& s2eqind, bool& stateequal) {
    int delta = s1p - s1eqind;
    int s2future = s2p + delta;
    if (s2future < str2.length()) {
        if (str1[s1p] < str2[s2future]) { //previous call was correct
            //    |
            // CABFCCC
            // CABGDDD
            // |
            stateequal = false;
        } else if (str1[s1p] > str2[s2future]) {
            //    |
            // CABFCCC
            // CABEDDD
            // |
            s2p = s2future;
            s1p = s1eqind;
            stateequal = false;
        } else {
            //    |
            // CABFCCC
            // CABFDDD
            // |
            stateequal = false; //PROGRAMMER BEWARE! Deceptive.
        }
    } else {
        //    |
        // CABFCCC
        // CAB
        // |
        //s2p = s2future;
        //s1p = s1eqind;
        stateequal = false;
    }
}


void processStrings(const string& str1, const string& str2) {
    string ret;
    int s1p=0, s2p=0;
    int s1eqind = -1, s2eqind = -1;

    //stateequal denotes the following invariant
    //  Everything from [s1eqind, s1p] is the same as everything from [s2eqind, s2eqind + (s1eqind - s1p)]
    bool stateequal = false;
    while (s1p < str1.length() && s2p < str2.length()) {
        if (stateequal) {
            int len = s1p - s1eqind;
            if (s1p < str1.length() && (s2p + len) < str2.length()) {
                assert(str1.substr(s1eqind, len) == str2.substr(s2eqind, len));
            }
        }
        if (str1[s1p] < str2[s2p]){
            if (stateequal) {
                processStateLesser(ret, str1, str2, s1p, s2p, s1eqind, s2eqind, stateequal);
            } else {
                ret.push_back(str1[s1p++]);
            }
        }else if (str1[s1p] > str2[s2p]){
            if (stateequal) {
                processStateGreater(ret, str1, str2, s1p, s2p, s1eqind, s2eqind, stateequal);
            } else {
                ret.push_back(str2[s2p++]);
            }
        } else {
            if (stateequal == false) {
                stateequal = true;
                s1eqind = s1p;
                s2eqind = s2p;
                ret.push_back(str1[s1p++]); //choose str1 speculatively
            } else {
                processStateEqual(ret, str1, str2, s1p, s2p, s1eqind, s2eqind, stateequal);
            }
        }
        if (stateequal && s1p == str1.length()) { //and we are in equal state, swap
            int delta = s1p - s1eqind;
            int s2pfuture = s2p + delta;
            s2p = s2pfuture;
            s1p = s1eqind;
            stateequal = false;
        }
    }

    if (s1p < str1.length()) {
        ret += str1.substr(s1p);
    } else if (s2p < str2.length()) {
        ret += str2.substr(s2p);
    }

    std::cout << ret << std::endl;;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        string str1, str2;
        std::cin >> str1;
        std::cin >> str2;
        processStrings(str1, str2);
    }
}

