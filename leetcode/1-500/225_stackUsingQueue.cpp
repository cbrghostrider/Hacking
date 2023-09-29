// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Stack {
    queue<int> myqueue;
public:
    // Push element x onto stack.
    void push(int x) {
        myqueue.push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        if (myqueue.empty()) return;
        queue<int> tmpqueue;
        while (myqueue.size() > 1) {
            int item = myqueue.front(); myqueue.pop();
            tmpqueue.push(item);
        }
        myqueue = tmpqueue;
    }

    // Get the top element.
    int top() {
        if (myqueue.empty()) return 0; //change to throw later
        queue<int> tmpqueue;
        int item;
        while (!myqueue.empty()) {
            item = myqueue.front(); myqueue.pop();
            tmpqueue.push(item);
        }
        myqueue = tmpqueue;
        return item;
    }

    // Return whether the stack is empty.
    bool empty() {
        return myqueue.empty();
    }
};
