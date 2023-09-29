// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Note: You must use only standard operations of a stack -- 
// which means only push to top, peek/pop from top, size, and 
// is empty operations are valid.
//
class Queue {
    vector<int> stack;
    vector<int> tempstack;
public:
    // Push element x to the back of queue.
    // complexity O(n)
    void push(int x) {
        while (!stack.empty()) {
            tempstack.push_back(stack.back());
            stack.pop_back();
        }
        stack.push_back(x);
        while (!tempstack.empty()) {
            stack.push_back(tempstack.back());
            tempstack.pop_back();
        }
    }

    // Removes the element from in front of queue.
    // complexity O(1)
    void pop(void) {
        if (empty()) return;
        stack.pop_back();
    }

    // Get the front element.
    // complexity O(1)
    int peek(void) {
        if (empty()) return -1; //error, maybe throw exception
        return stack.back();
    }

    // Return whether the queue is empty.
    // complexity O(1)
    bool empty(void) {
        return (stack.empty());
    }
};
