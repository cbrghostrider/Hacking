// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Better solution this time. I'm keeping an instack and outstack.
// Instack just stores contiguous pushes in O(1) time
// When we get the first pop, we will move all current (n) pushed values from
// instack to outstack. These take O(n) time, but we can pretend that the original 
// pushes took (O(1) + O(1)) time... in other words...
// the cost of the pop is amortized O(1)
//

class Queue {
    vector<int> instack;
    vector<int> outstack;
public:
    // Push element x to the back of queue.
    // complexity O(1)
    void push(int x) {
        instack.push_back(x);
    }

    // Removes the element from in front of queue.
    // complexity O(1) amortized
    void pop(void) {
        if (instack.empty() && outstack.empty()) return;
        if (!outstack.empty()) { outstack.pop_back(); return;}
        
        //move stuff from instack to outstack
        while (!instack.empty()) {
            outstack.push_back(instack.back());
            instack.pop_back();
        }
        outstack.pop_back(); //and do the pop
        return;
    }

    // Get the front element.
    // complexity O(1) amortized
    int peek(void) {
        if (instack.empty() && outstack.empty()) return -1; //error, maybe throw exception
        if (!outstack.empty()) { return outstack.back();}
        
        //move stuff from instack to outstack
        while (!instack.empty()) {
            outstack.push_back(instack.back());
            instack.pop_back();
        }
        return outstack.back(); //and do the pop
    }

    // Return whether the queue is empty.
    // complexity O(1)
    bool empty(void) {
        return (instack.empty() && outstack.empty());
    }
};
