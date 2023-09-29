/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
    int surplus=-1;
    bool has_surplus = false;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        if (has_surplus) return surplus;
        if (!Iterator::hasNext()) return -1;  // nothing to peek
        has_surplus = true;
        surplus = Iterator::next();
        return surplus;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
	    if (has_surplus) {
            has_surplus = false;
            return surplus;
        }
        if (!Iterator::hasNext()) return -1;  // nothing to do
        return Iterator::next();
	}
	
	bool hasNext() const {
	    if (has_surplus) return true;
        return Iterator::hasNext();
	}
};
