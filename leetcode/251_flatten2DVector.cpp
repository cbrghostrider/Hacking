// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Vector2D {
    vector<vector<int>>& vecref;  //Note this is reference, not a copy. 
    vector<vector<int>>::iterator rowit;
    vector<int>::iterator colit;

    void adjustColIt() {
        while (colit == rowit->end()) {
            rowit++;
            if (rowit != vecref.end()) {
                colit = rowit->begin();
            } else {
                break;
            }
        }
    }

public:
    Vector2D(vector<vector<int>>& vec2d) 
    : vecref(vec2d), rowit(), colit() {
        rowit = vec2d.begin();
        if (rowit != vec2d.end()) {
            colit = rowit->begin();
            adjustColIt();
        }
    }

    int next() {
        if (!hasNext()) return -1; //maybe throw?
        int retval = *colit;
        colit++;
        adjustColIt();
        return (retval);
    }

    bool hasNext() {
        return (!(rowit == vecref.end()));
    }
};
