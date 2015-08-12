// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <algorithm>

// Forward declaration of the read4 API.

char BUFFER[] = "ab";
int  BSIZE = 2;

int bptr = 0;

int read4(char *buf) {
    int leftover = BSIZE - bptr;
    int retval = std::min(4, leftover);
    for (int i=0; i<retval; i++) {
        buf[i] = BUFFER[bptr++];
    }
    return retval;
}

class Solution {
    char readBuf[4];  //always read into here (always stored from start, even if fewer than 4)
    int  holds = 0;   //how many bonus values do I have
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    
    //called when n <= holds
    void needsLessThanWeAlreadyHave(char* buf, int& bufptr, int& holds, int& n) {
        if (n == 0) return;
        
        for (int ctr=0; ctr < n; ctr++) {    //copy over stuff that is needed
            buf[bufptr++] = readBuf[ctr];
            holds--;
        }
        for (int ctr=0; ctr<holds; ctr++) {  //and adjust the internal buffer
            readBuf[ctr] = readBuf[ctr + n];
        }
        n = 0;
    }
    
    //called when n > holds and holds is non-zero; so offload all that we have
    void needsMoreThanWeAlreadyHave(char* buf, int& bufptr, int& holds, int& n) {
        for (int ctr=0; ctr<holds; ctr++) {
            buf[bufptr++] = readBuf[ctr];
        }
        n -= holds;
        holds = 0;
    }
    
    //called when n is non-zero and holds is 0
    //return value indicates if we need to stop
    bool needsSomeAndWeHaveNone(char* buf, int& bufptr, int& holds, int& n) {
        holds = read4(readBuf);
        bool stopEarly = (holds != 4);
        if (holds == 0) return stopEarly;
        
        if (n <= holds) {
            needsLessThanWeAlreadyHave(buf, bufptr, holds, n);
        } else {
            needsMoreThanWeAlreadyHave(buf, bufptr, holds, n);
        }
        return stopEarly;
    }
    
    int read(char *buf, int n) {
        int bufptr = 0;  //denotes next place to write to
        while (n) {
            if (n <= holds) {        //need less than or equal to what we already have
                needsLessThanWeAlreadyHave(buf, bufptr, holds, n);
            } else if (holds != 0) { //need more than we have, but we have some lying around
                needsMoreThanWeAlreadyHave(buf, bufptr, holds, n);
            } else {                 //need to perform API read
                bool breakNow = needsSomeAndWeHaveNone(buf, bufptr, holds, n);
                if (breakNow) break;
            }
        }
        return (bufptr);
    }
};

void performRead(Solution& sln, int n) {
    char localbuffer[1000];
    int ret = sln.read(localbuffer, n);
    for (int i=0; i<ret; i++) {
        printf("%c", localbuffer[i]);
    }
    printf("\n");
}

int main() {
    Solution sln;
    performRead(sln, 1);
    performRead(sln, 2);
}
