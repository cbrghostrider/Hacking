class MaxStack {
    vector<int> stack;
    void repopulateAt(int index) {
        for (int i=index; i<stack.size()-1; i++) {
            std::swap(stack[i], stack[i+1]);
        }
        stack.pop_back();
    }
public:
    // O(1) time.
    MaxStack() {}
    
    // O(1) time.
    void push(int x) {
        stack.push_back(x);
    }
    
    // O(1) time.
    int pop() {
        int ret = stack.back();
        stack.pop_back();
        return ret;
    }
    
    // O(1) time.
    int top() {
        return stack.back();
    }
    
    // O(n) time.
    int peekMax() {
        int max = std::numeric_limits<int>::min();
        for (int i=0; i<stack.size(); i++) {
            if (stack[i] > max) {max = stack[i];}
        }
        return max;
    }
    
    // O(n) time.
    int popMax() {
        int max = peekMax();
        for (int i=stack.size()-1; i>=0; i--) {
            if (stack[i] == max) {
                repopulateAt(i);
                break;
            }
        }
        return max;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
