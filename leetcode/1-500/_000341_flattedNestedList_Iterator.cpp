/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
    // This class invariant is as follows:
    //
    // 1. Either the index points to a "vanilla" integer within nlist
    // 2. Or the index points to a nested list within nlist, and iter deals with that
    // 
    // Note that 2 also implies that iter->hasNext() will be true
    // If that is to not be the case, internal state will be adjusted (moving the next index, etc.)
    //
    vector<NestedInteger>& nlist;
    
    int index = 0;                 // where in my list am I
    NestedIterator* iter=nullptr;  // for dealing with nested-ness within my list
    bool done=false;
    
    // fast forwards internal state so we are in a position to return the next "vanilla" integer
    void fastForward(int i) {
        for (; i<nlist.size(); i++) {
            index = i;
            if (nlist[i].isInteger()) {   // next int to be returned is ready
                delete iter;
                iter = nullptr; 
                return; 
            }
            iter = new NestedIterator(const_cast<vector<NestedInteger>&>(nlist[i].getList()));
            if (iter->hasNext()) { 
                return; 
            }
        }
        done = true;
    }
        
public:
    NestedIterator(vector<NestedInteger> &nestedList) : nlist(nestedList) {
        if (nlist.size() == 0) {
            done = true; 
            return;
        }
        fastForward(0);        
    }
    
    int next() {
        if (!hasNext()) return -1;  // shouldn't be called
        
        if (nlist[index].isInteger()) {
            int ret = nlist[index].getInteger();
            fastForward(index+1);
            return ret;
        }
        
        int ret = iter->next();
        if (!iter->hasNext()) {
            fastForward(index+1);
        }
        return ret;
    }
    
    bool hasNext() {
        return !done;
    }
};


/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
