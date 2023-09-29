class Solution {
public:
    // O(n) time, O(n) space.
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        vector<int> stack;
        int push_ptr=0, pop_ptr=0; // points to next value to be consumed.

        while (push_ptr < pushed.size() && pop_ptr < popped.size()) {
            if (stack.empty() || stack.back() != popped[pop_ptr]) {
                while (push_ptr < pushed.size() && pushed[push_ptr] != popped[pop_ptr]) {
                    stack.push_back(pushed[push_ptr++]);
                    if (push_ptr == pushed.size()) return false;
                }
                if (push_ptr != pushed.size()) {
                    stack.push_back(pushed[push_ptr++]);
                }
            } else {
                stack.pop_back();
                pop_ptr++;
            }
        }
        while (pop_ptr < popped.size()) {
            if (stack.empty()) return false;
            if (stack.back() != popped[pop_ptr]) return false;
            stack.pop_back();
            pop_ptr++;
        }
        
        // push_ptr not done here simply means that stuff will later be pushed to a stack, 
        // but not popped, and that's OK.
        return true;
    }
};
