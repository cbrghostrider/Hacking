//first attempt.. works fine, but kinda messy
class Solution {
    unordered_map<int, char> roman = {{1000, 'M'}, {500, 'D'}, {100, 'C'}, {50, 'L'}, {10, 'X'}, {5, 'V'}, {1, 'I'}};
    vector<int> keys = {1000, 500, 100, 50, 10, 5, 1};
    string retval;
        
    bool powerOfTen_(int val) {
        return (val == 1 || val == 10 || val == 100 || val == 1000);
    }
    
    void representSubtraction_(int indexBig, int indexSmall) { //represents the subtraction of two terms
        retval += roman[keys[indexSmall]];
        retval += roman[keys[indexBig]];
    }
    
    void intToRomanPrime_(int num, int keyIndex) {
        if (num == 0) return;
        int numq = num / keys[keyIndex];
        
        if (!powerOfTen_(keys[keyIndex])) { //handle 5, 50, 500...
            if (num >= (keys[keyIndex-1] - keys[keyIndex+1])) { //between [90,100) for example
                representSubtraction_(keyIndex-1, keyIndex+1);
                int numConv = num - (keys[keyIndex-1] - keys[keyIndex+1]);
                intToRomanPrime_(numConv, keyIndex+1);
            } else if ((num >= (keys[keyIndex] - keys[keyIndex+1])) && (num < keys[keyIndex])) { //between [40, 50) for example
                representSubtraction_(keyIndex, keyIndex+1);
                int numConv = num - (keys[keyIndex] - keys[keyIndex+1]);
                intToRomanPrime_(numConv, keyIndex+1);
            } else{ //number between 1 and 39 or 51 and 89 for example
                if (numq == 1) retval += roman[keys[keyIndex]];
                int numConv = (numq == 1) ? (num - keys[keyIndex]) : num;
                intToRomanPrime_(numConv, keyIndex+1);
            }
	    return;
        }
        if (numq > 3) { //cannot have more than 3
            representSubtraction_(keyIndex-1, keyIndex);
            int numConv = num - (keys[keyIndex - 1] - keys[keyIndex]);
            intToRomanPrime_(numConv, keyIndex+1);
            return;
        }
        for (int i=0; i<numq; i++) {
            retval += roman[keys[keyIndex]];
        }
        intToRomanPrime_(num % keys[keyIndex], keyIndex+1);
        return;
    }
    
public:
    string intToRoman(int num) {
        if (num == 0) return ""; //zero not defined on roman scale 
        retval = "";
        intToRomanPrime_(num, 0);
        return retval;
    }
};
