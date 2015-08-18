// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
    char readBuf[4];
    int rbptr=0;
    int available=0;
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int bufptr=0;
        while (n) {
            if (available) {
                buf[bufptr++] = readBuf[rbptr];
                rbptr = (rbptr+1) % 4;
                available--;
                n--;
                continue;
            } else {
                available = read4(readBuf);
                rbptr=0;
                if (available == 0) return bufptr;
                continue;
            }
        }
        return bufptr;
    }
};
