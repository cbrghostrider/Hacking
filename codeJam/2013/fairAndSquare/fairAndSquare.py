# -------------------------------------------------------------------------------------
#         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
#                       For email, run on linux (perl v5.8.5):
#   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
# -------------------------------------------------------------------------------------
#!/usr/bin/python
import sys
import math

def isPalindrome (num):
    numStr = str(num)
    revStr = numStr[::-1]
    if numStr == revStr:
        return True
    else :
        return False

# construct a list of palindromes of length dig
# make sure these are between [lowerBnd, upperBnd]
def constructPalin (dig, lowerBnd, upperBnd):
    myList = []
    digCtr = dig // 2
    if dig % 2 == 1:
        digCtr += 1 
    lowerCnt = 10 ** (digCtr - 1)
    upperCnt = 10 ** (digCtr)
    for num in range (lowerCnt, upperCnt) :
        strRepr = str(num)
        revRepr = strRepr[::-1]
        if (dig % 2 == 1) :
            strRepr = strRepr[:-1] 
        strNum = strRepr + revRepr
        myList.append(int(strNum))
    return myList

def solveTest (a, b):
    ap = math.floor(math.sqrt(a))
    bp = math.ceil(math.sqrt(b))
    da = len(str(ap))
    db = len(str(bp))
    num = 0  # counter for answer
    for d in range (da, (db+1)):
        setPprd = constructPalin(d, ap, bp)
        for ppr in setPprd:
            p = ppr * ppr
            if (p < a or p > b) or (not isPalindrome(p)) :
                continue
            else: 
                num += 1
    return num

def readInput (filename):
    with open(filename) as ip:
        myInput = [line.rstrip('\n') for line in ip]
    return myInput

def processInput (lines):
    num, *tests = lines
    for n in range (1, (int(num)+1)):
        a, b = map (int, tests[n-1].split(" "))
        result = solveTest(a, b)
        print ('Case #%d: %d' % (n , result))

if __name__ == '__main__' :
    lines = readInput(sys.argv[1])
    processInput(lines)
