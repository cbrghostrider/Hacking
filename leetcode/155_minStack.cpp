class MinStack {
    vector<int> minIndices; //keeps track of indices of minimum elements
    vector<int> stack;      //actual stack for elements
public:
    void push(int x) {
        if (minIndices.size() == 0 || x <= getMin()) {
            minIndices.push_back(stack.size());                
        }
        stack.push_back(x);
    }

    void pop() {
        if (minIndices.size() && minIndices.back() == (stack.size()-1)) {
            minIndices.pop_back();
        }
        if (stack.size()) stack.pop_back();
    }

    int top() {
        return stack.back();
    }

    int getMin() {
        return stack[minIndices.back()];
    }
};
